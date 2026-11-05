import os
import subprocess
import pygame
#this file only displays the game window

#file paths
projectFolder = os.path.dirname(os.path.abspath(__file__))
exePath = os.path.join(projectFolder, "cmake-build-debug", "ui.exe")
csvPath = os.path.join(projectFolder, "resources", "food.csv")

#basic window setting & title
width = 900
height = 700
title = "Restricted Eater? I hardly know her!"
