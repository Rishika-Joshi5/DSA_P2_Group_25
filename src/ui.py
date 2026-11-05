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


