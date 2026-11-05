import os
import subprocess
import pygame
#this file only displays the game window

#file paths
projectFolder = os.path.dirname(os.path.abspath(__file__))
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


