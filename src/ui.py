import os
import subprocess
import pygame
#this file only displays the game window

#file paths
projectFolder = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
exePath = os.path.join(projectFolder, "cmake-build-debug", "ui.exe")
csvPath = os.path.join(projectFolder, "resources", "food.csv")

#basic window settings, colors, and title
width = 900
height = 700
title = "Restricted Eater? I hardly know her!"
background = (201, 215, 190)   #sage green
textColor = (36, 71, 48)       #dark green
buttons = (232, 130, 160)      #pink
selected_buttons = (205, 100, 135)    #darker pink
highlights = (252, 226, 234)     #lighter pink
white = (255, 255, 255)
gray = (120, 135, 125)
lineColor = (205, 220, 205)
percentColor = (88, 160, 90)     #green
errorColor = (190, 40, 40)       #red

pygame.init()
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption(title)
clock = pygame.time.Clock()

titleFont = pygame.font.SysFont("georgia", 34, bold=True)
font = pygame.font.SysFont("verdana", 18)
smallFont = pygame.font.SysFont("verdana", 15)

#slenderman picture
slenderImage = pygame.image.load(os.path.join(projectFolder, "resources", "slenderman.png")).convert_alpha()
slenderImage = pygame.transform.smoothscale(slenderImage, (97, 120))

#helper functions -------------
def draw_text(text, text_font, color, x, y, center = False):
    picture = text_font.render(text, True, color)
    if center:
        screen.blit(picture, picture.get_rect(center = (x, y)))
    else:
        screen.blit(picture, (x, y))

def shorten(text, text_font, max_width):
    if text_font.size(text)[0] <= max_width:
        return text
    while len(text) > 0 and text_font.size(text + "...")[0] > max_width:
        text = text[:-1]
    return text + "..."

def draw_button(rect, text, enabled = True):
    color = buttons
    if not enabled:
        color = lineColor
    elif rect.collidepoint(pygame.mouse.get_pos()):
        color = selected_buttons
    pygame.draw.rect(screen, color, rect, border_radius = 8)
    draw_text(text, font, white, rect.centerx, rect.centery, center = True)

#reads food.csv to get every food category and every nutrient name
def load_options():
    foods = []
    nutrients = []
    file = open(csvPath, encoding = "utf-8", errors = "replace")

    #first line has the column names
    headers = file.readline().strip().split('","')
    for header in headers:
        header = header.strip().strip('"')
        if header.startswith("Data."):
            nutrients.append(header[5:])   #remove "Data."

    #the food category is the first column of every other line
    for line in file:
        category = line.split('","')[0].strip().strip('"')
        if category != "" and category not in foods:
            foods.append(category)

    file.close()
    foods.sort()
    return foods, nutrients

#turns what ui.exe printed into the original food and a list of results
def read_output(text):
    original = None
    results = []
    times = {}
    started = False
    category = ""
    name = ""

    for line in text.splitlines():
        line = line.strip()
        if line.startswith("ROOT|"):
            #display - ROOT|category|name|amount|units
            parts = line.split("|")
            original = {"category": parts[1], "name": parts[2],
                        "amount": float(parts[3]), "units": parts[4]}
        elif line == "START":
            started = True
        elif line == "BFS_START":
            started = False
        elif line.startswith("TIME|"):
            parts = line.split("|")
            times[parts[1]] = float(parts[2])
        elif started and line.startswith("Food Type: "):
            category = line[len("Food Type: "):]
        elif started and line.startswith("Food Name: "):
            name = line[len("Food Name: "):]
        elif started and " of " in line and original is not None:
            amountText = line.split(" of ")[0]
            amountText = amountText[:len(amountText) - len(original["units"])]
            results.append({"category": category, "name": name, "amount": float(amountText)})

    if original is None:
        return None, [], {}

    for i in range(len(results)):
        if results[i]["name"] == original["name"]:
            results.pop(i)
            break

    for food in results:
        food["match"] = match_percent(original["amount"], food["amount"])
    results.sort(key = lambda food: food["match"], reverse=True)
    return original, results, times
def match_percent(a, b):
    if a == b:
        return 100.0
    return 100.0 * min(a, b) / max(a, b)

def simplify_num(number):
    return f"{number:g}"

#dropdown menu -------------
class Dropdown:
    rowHeight = 32
    rowsShown = 8

    def __init__(self, x, y, boxWidth, placeholder, options, canSearch = False):
        self.rect = pygame.Rect(x, y, boxWidth, 40)
        self.placeholder = placeholder
        self.options = options
        self.canSearch = canSearch   #lets you type to find an option
        self.selected = None
        self.isOpen = False
        self.scroll = 0
        self.search = ""

    def matching_options(self):
        if self.search == "":
            return self.options
        matches = []
        for option in self.options:
            if self.search.lower() in option.lower():
                matches.append(option)
        return matches

    def search_bar_rect(self):
        return pygame.Rect(self.rect.x, self.rect.bottom, self.rect.width, self.rowHeight)

    def row_rect(self, i):
        top = self.rect.bottom
        if self.canSearch:
            top += self.rowHeight   #the search bar takes the first row
        return pygame.Rect(self.rect.x, top + i * self.rowHeight, self.rect.width, self.rowHeight)

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            if self.rect.collidepoint(event.pos):
                self.isOpen = not self.isOpen
                self.scroll = 0
                self.search = ""
            elif self.isOpen:
                options = self.matching_options()
                for i in range(self.rowsShown):
                    index = self.scroll + i
                    if index < len(options) and self.row_rect(i).collidepoint(event.pos):
                        self.selected = options[index]
                #closes the list unless they clicked the search bar
                if not (self.canSearch and self.search_bar_rect().collidepoint(event.pos)):
                    self.isOpen = False

        elif event.type == pygame.MOUSEWHEEL and self.isOpen:
            self.scroll -= event.y * 3
            biggestScroll = max(0, len(self.matching_options()) - self.rowsShown)
            self.scroll = max(0, min(self.scroll, biggestScroll))

        elif event.type == pygame.KEYDOWN and self.isOpen and self.canSearch:
            if event.key == pygame.K_BACKSPACE:
                self.search = self.search[:-1]
            elif event.unicode != "" and event.unicode.isprintable():
                self.search += event.unicode
            self.scroll = 0

    def draw_box(self):
        pygame.draw.rect(screen, white, self.rect, border_radius=6)
        pygame.draw.rect(screen, textColor, self.rect, 2, border_radius=6)
        if self.selected is None:
            text, color = self.placeholder, gray
        else:
            text, color = self.selected, textColor
        draw_text(shorten(text, smallFont, self.rect.width - 40), smallFont, color,
                  self.rect.x + 10, self.rect.y + 10)
        draw_text("v", smallFont, textColor, self.rect.right - 22, self.rect.y + 10)

    def draw_list(self):
        if not self.isOpen:
            return
        if self.canSearch:
            bar = self.search_bar_rect()
            pygame.draw.rect(screen, highlights, bar)
            pygame.draw.rect(screen, textColor, bar, 1)
            if self.search == "":
                draw_text("Type to search, scroll for more", smallFont, gray, bar.x + 10, bar.y + 7)
            else:
                draw_text(shorten(self.search + "|", smallFont, bar.width - 20), smallFont, textColor,
                          bar.x + 10, bar.y + 7)

        options = self.matching_options()
        if len(options) == 0:
            row = self.row_rect(0)
            pygame.draw.rect(screen, white, row)
            pygame.draw.rect(screen, lineColor, row, 1)
            draw_text("No matches", smallFont, gray, row.x + 10, row.y + 7)

        for i in range(self.rowsShown):
            index = self.scroll + i
            if index >= len(options):
                break
            row = self.row_rect(i)
            color = white
            if row.collidepoint(pygame.mouse.get_pos()):
                color = highlights
            pygame.draw.rect(screen, color, row)
            pygame.draw.rect(screen, lineColor, row, 1)
            draw_text(shorten(options[index], smallFont, row.width - 20), smallFont, textColor,
                      row.x + 10, row.y + 7)

#setting up the screen -------------
foodOptions, nutrientOptions = load_options()

#the dropdown shows short names ("Calcium") but ui.exe needs the
nutrientFullName = {}
for nutrient in nutrientOptions:
    nutrientFullName[nutrient.split(".")[-1]] = nutrient

foodBox = Dropdown(40, 135, 360, "Choose a food", foodOptions, canSearch = True)
nutrientBox = Dropdown(420, 135, 240, "Choose a nutrient", list(nutrientFullName.keys()))
countBox = Dropdown(680, 135, 90, "How many?", [str(n) for n in range(1, 11)])
dropdowns = [foodBox, nutrientBox, countBox]

searchButton = pygame.Rect(785, 135, 75, 40)
restartButton = pygame.Rect(40, 650, 120, 40)
panel = pygame.Rect(40, 200, 820, 435)

state = "choose"      #can be "choose", "searching", or "results"
message = ""
process = None
searchStart = 0
original = None
results = []
times = {}
nutrientLabel = ""

def restart():
    global state, message, original, results
    for box in dropdowns:
        box.selected = None
        box.isOpen = False
    state = "choose"
    message = ""
    original = None
    results = []

def start_search():
    global state, message, process, searchStart, nutrientLabel
    if foodBox.selected is None or nutrientBox.selected is None or countBox.selected is None:
        message = "Choose a food, a nutrient, and how many results first."
        return
    nutrientLabel = nutrientBox.selected
    try:
        process = subprocess.Popen(
            [exePath, foodBox.selected, nutrientFullName[nutrientLabel], countBox.selected],
            cwd = os.path.dirname(exePath),
            stdout = subprocess.PIPE, stderr = subprocess.PIPE, text = True, errors = "replace")
    except FileNotFoundError:
        message = "ui.exe was not found. Check exePath at the top of ui.py."
        return
    message = ""
    state = "searching"
    searchStart = pygame.time.get_ticks()

def check_search():
    global state, message, original, results, times
    waited = pygame.time.get_ticks() - searchStart
    #wait at least 1.2 seconds for "Searching..."
    if process.poll() is None or waited < 1200:
        return
    output, errors = process.communicate()
    original, results, times = read_output(output)
    if original is None:
        state = "choose"
        message = "The search did not work: " + (output + errors).strip()
    else:
        state = "results"


#drawing the output area -------------
def draw_panel():
    pygame.draw.rect(screen, white, panel, border_radius=12)
    pygame.draw.rect(screen, lineColor, panel, 2, border_radius=12)

    if state == "choose":
        if message != "":
            draw_text(shorten(message, font, panel.width - 40), font, errorColor, panel.centerx, panel.centery,
                      center = True)
        else:
            draw_text("Pick your three options above, then press Search.", font, gray,
                      panel.centerx, panel.centery, center = True)

    elif state == "searching":
        dots = "." * ((pygame.time.get_ticks() // 300) % 4)
        x = panel.centerx - titleFont.size("Searching...")[0] // 2
        draw_text("Searching" + dots, titleFont, buttons, x, panel.centery - 50)

        #block sliding animation
        track = pygame.Rect(panel.centerx - 150, panel.centery + 15, 300, 12)
        pygame.draw.rect(screen, lineColor, track, border_radius=6)
        position = (pygame.time.get_ticks() // 4) % 480
        if position > 240:
            position = 480 - position
        pygame.draw.rect(screen, percentColor, (track.x + position, track.y, 60, 12), border_radius=6)

    elif state == "results":
        draw_results()


def draw_results():
    #the food the user picked
    box = pygame.Rect(panel.x + 15, panel.y + 15, panel.width - 30, 80)
    pygame.draw.rect(screen, highlights, box, border_radius=10)
    amountText = simplify_num(original["amount"]) + " " + original["units"] + " of " + nutrientLabel
    amountWidth = font.size(amountText)[0]
    draw_text("Your food", smallFont, selected_buttons, box.x + 15, box.y + 8)
    draw_text(shorten(original["name"], font, box.width - amountWidth - 50), font, textColor,
              box.x + 15, box.y + 30)
    draw_text("Category: " + original["category"], smallFont, gray, box.x + 15, box.y + 55)
    draw_text(amountText, font, selected_buttons, box.right - 15 - amountWidth, box.y + 30)

    #the most similar foods
    y = box.bottom + 15
    draw_text("Most similar foods", font, textColor, panel.x + 20, y)
    if "DFS" in times and "BFS" in times:
        timeText = f"DFS: {times['DFS']:.4f} ms    BFS: {times['BFS']:.4f} ms"
        draw_text(timeText, smallFont, selected_buttons, panel.right - 20 - smallFont.size(timeText)[0], y + 2)
    y += 32
    if len(results) == 0:
        draw_text("No other foods with this nutrient were found.", font, gray, panel.x + 20, y)
        return

    for i in range(len(results)):
        food = results[i]
        draw_text(shorten(str(i + 1) + ". " + food["name"], smallFont, 440), smallFont, textColor,
                  panel.x + 20, y)
        draw_text(simplify_num(food["amount"]) + " " + original["units"], smallFont, gray, panel.x + 480, y)

        #a bar that fills up based on the % match
        bar = pygame.Rect(panel.x + 590, y + 4, 130, 12)
        pygame.draw.rect(screen, lineColor, bar, border_radius=6)
        filled = pygame.Rect(bar.x, bar.y, int(bar.width * food["match"] / 100), bar.height)
        pygame.draw.rect(screen, percentColor, filled, border_radius=6)
        draw_text(f"{food['match']:.0f}%", smallFont, textColor, bar.right + 12, y)
        y += 29


#main loop -------------
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif state == "searching":
            pass   #ignore clicks while searching

        else:
            #if a dropdown list is open, only that dropdown gets the event
            openBox = None
            for box in dropdowns:
                if box.isOpen:
                    openBox = box
            if openBox is not None:
                openBox.handle_event(event)
            else:
                for box in dropdowns:
                    box.handle_event(event)
                if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    if searchButton.collidepoint(event.pos):
                        start_search()
                    elif restartButton.collidepoint(event.pos):
                        restart()

    if state == "searching":
        check_search()

    #drawing everything
    screen.fill(background)
    draw_text(title, titleFont, textColor, width // 2, 45, center = True)
    screen.blit(slenderImage, (width - 107, 5))
    draw_text("Find foods with about the same amount of a nutrient as the food you like.",
              smallFont, gray, width // 2, 85, center = True)

    draw_text("Food", smallFont, textColor, foodBox.rect.x, 112)
    draw_text("Nutrient", smallFont, textColor, nutrientBox.rect.x, 112)
    draw_text("Results", smallFont, textColor, countBox.rect.x, 112)

    for box in dropdowns:
        box.draw_box()
    draw_button(searchButton, "Search", state != "searching")

    draw_panel()

    draw_button(restartButton, "Restart", state != "searching")
    draw_text("Thank you for using Restricted Eater! Enjoy your meal.", smallFont, textColor,
              restartButton.right + 20, restartButton.y + 11)

    for box in dropdowns:
        box.draw_list()

    pygame.display.flip()
    clock.tick(60)

#stop ui.exe if the window is closed during a search
if process is not None and process.poll() is None:
    process.kill()
pygame.quit()
