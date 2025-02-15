
''' Inventory unlocking based on Achievement info
1 - pencil 
2 - crayon
3 - candy
4 - calculator
5 - microscope
6 - globe
7 - hat
8 - notebook
9 - trophy 
'''

import pygame
import sys
from achievements import isDone
from player import currentUser
from button import Button
from player import *

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Inventory')

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 200, 0)
BRIGHT_GREEN = (144, 238, 144)  # Lighter green for table background
RED = (200, 0, 0)
BRIGHT_RED = (255,0,0)
FONT3 = pygame.font.Font("font2.ttf", 45)
FONT = pygame.font.Font("font.ttf", 13)
FONT1 = pygame.font.Font("font.ttf", 9)

button_image = pygame.image.load("button4.png")
equip_buttons = []
backdrop = pygame.image.load("backdrop.png")  # Load the additional image
scaled_backdrop = pygame.transform.scale(backdrop, (750,320))  # Setting desired size

backpack = pygame.image.load("backpack.png")  # Load the additional image
scaled_backpack = pygame.transform.scale(backpack, (180,180))  # Setting desired size

# Load assets
BG = pygame.image.load("bg3.png")  # Background image
locked_image_original = pygame.image.load("lockeditem.png")
# Scale the locked image
locked_image = pygame.transform.scale(locked_image_original, (110, 110))


# Item images and names
item_names = ["pencil1", "crayon1", "candy1", "calculator1", "micro1", "globe1", "hat1", "book1", "trophy1"]
# Desired size for all item images
item_size = (100, 100)  # Width, Height

# Load and scale item images
item_images = {name: pygame.transform.scale(pygame.image.load(f"{name}.png"), item_size) for name in item_names}

def add_equip_button(screen, item_pos_x, item_pos_y, mouse_pos):
    """
    Helper method that ddds an "Equip" button beneath each unlocked item.

    :param screen: The screen that this is displayed on.
    :param item_pos_x: The x-coordinate of the button.
    :param item_pos_y: The y-coordinate of the button.
    :param mouse_pos: The position the mouse is in.

    :return: The equip button.
    """
    equip_button = Button(image=None, pos=(item_pos_x + 50, item_pos_y + 110), text_input="Equip", font=FONT1,
                          base_color=GREEN, hovering_color=BRIGHT_GREEN)
    equip_button.changeColor(mouse_pos)
    equip_button.update(screen)
    return equip_button



def on_equip_button_pressed(id):
    """
    Helper method that returns the ID of the item when the equip button is pressed.

    :param id: The ID of the item that the user wants to equip.

    :return: void method; Does not return anything.
    """

    print(id)
    player = currentUser("accounts.txt")
    player.setAvatarID(id)
    saveUser(player)
    print(currentUser("accounts.txt").getAvatarID())

def go_to_main_menu():
    """
    Helper method that returns to the main menu

    :return: void method; Does not return anything.
    """

    from mainmenupage import main_menu
    main_menu()
    print("Back to main menu")

def draw_items(screen, player):
    """
    Helper method that draws the inventory items that the player has onto the backpack screen.

    :param screen: The screen that will be drawn on.
    :param player: Player that will have their stats checked for inventory items.

    :return: void method; Does not return anything.
    """
    item_pos_x = 100  # Starting x position
    item_pos_y = 160  # Starting y position
    item_spacing_x = 150  # Space between items horizontally
    item_spacing_y = 150  # Space between items vertically

    for i, (name, image) in enumerate(item_images.items(), start=1):

        # Check if the corresponding achievement is unlocked
        if isDone(player, i):
            screen.blit(image, (item_pos_x, item_pos_y))
            # add button to equip avatar
            mouse_pos = pygame.mouse.get_pos()
            # add button to list
            equip_buttons.append((add_equip_button(screen, item_pos_x, item_pos_y, mouse_pos), i))
        else:
            #print(isDone(player,i))
            screen.blit(image, (item_pos_x, item_pos_y))
            # Overlay the locked image centered on the item image
            lock_x = item_pos_x + (item_size[0] - locked_image.get_width()) / 2
            lock_y = item_pos_y + (item_size[1] - locked_image.get_height()) / 2
            screen.blit(locked_image, (lock_x, lock_y))

        # Arrange items in rows
        item_pos_x += item_spacing_x
        if item_pos_x + item_size[0] > SCREEN.get_width():
            item_pos_x = 100  # Reset to first column
            item_pos_y += item_spacing_y  # Move to the next row


def inventory_screen():
    """
    Helper method that runs the inventory screen when called on.

    :return: void method; Does not return anything.
    """
    back_button = Button(image=button_image, pos=(110, 570), text_input="Back to Main Menu", font=FONT1,
                              base_color=GREEN,hovering_color=BRIGHT_GREEN)

    running = True
    player = currentUser("accounts.txt")  # Retrieve the current player object

    while running:
        keys = pygame.key.get_pressed()
        if keys[pygame.K_ESCAPE]:
            go_to_main_menu()
        if keys[pygame.K_1]:
            on_equip_button_pressed(1)
        if keys[pygame.K_2]:
            on_equip_button_pressed(2)
        if keys[pygame.K_3]:
            on_equip_button_pressed(3)
        if keys[pygame.K_4]:
            on_equip_button_pressed(4)
        if keys[pygame.K_5]:
            on_equip_button_pressed(5)
        if keys[pygame.K_6]:
            on_equip_button_pressed(6)
        if keys[pygame.K_7]:
            on_equip_button_pressed(7)
        if keys[pygame.K_8]:
            on_equip_button_pressed(8)
        if keys[pygame.K_9]:
            on_equip_button_pressed(9)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                if back_button.checkForInput(mouse_pos):
                    go_to_main_menu()
                for button, id in equip_buttons:
                    if button.checkForInput(mouse_pos):
                        on_equip_button_pressed(id)


        SCREEN.fill(WHITE)
        SCREEN.blit(BG, (0, 0))
        SCREEN.blit(scaled_backdrop, (80, 150))
        SCREEN.blit(scaled_backpack, (710, 410))
        draw_items(SCREEN, player)

        title_text = FONT3.render("Backpack", True, RED)
        SCREEN.blit(title_text, (280, 50))

        title2_text = FONT.render("Complete Achievements to unlock items!", True, "Black")
        SCREEN.blit(title2_text, (200, 120))

        mouse_pos = pygame.mouse.get_pos()
        back_button.changeColor(mouse_pos)
        back_button.update(SCREEN)


        pygame.display.update()

    pygame.quit()
    sys.exit()

if __name__ == '__main__':
    inventory_screen()
