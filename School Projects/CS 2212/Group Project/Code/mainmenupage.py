import pygame
import sys
from button import Button
from player import Player, currentUser
from gameboardscreen import Level1Board, Level2Board, Level3Board

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Main Menu')

WHITE = (255, 255, 255)
GREEN = (0, 200, 0)
BRIGHT_GREEN = (0, 255, 0)
RED = (200, 0, 0)
BRIGHT_RED = (255, 0, 100)

# Load assets
BG = pygame.image.load("bg3.png")  # Background image added

# more images
button_image = pygame.image.load("button5.png")
button_image2 = pygame.image.load("button4.png")

def get_font(size):
    """
    Helper method that returns the font.

    :param size: The size of the font.

    :return: The font and the font size.
    """

    # Function to get the desired font
    return pygame.font.Font("font.ttf", size)

def get_font2(size):
    """
    Helper method that returns the second font.

    :param size: The size of the font.

    :return: The second font and the font size.
    """

    # Function to get the desired font
    return pygame.font.Font("font2.ttf", size)

def new_game():
    """
    Helper method that starts a new game.

    :return: void method; Does not return anything.
    """
    board = Level1Board(SCREEN)  # Create an instance of Level1Board
    board.run()
    print("New Game")

def inventory():
    """
    Helper method that goes to the inventory screen.

    :return: void method; Does not return anything.
    """

    from backpackscreen import inventory_screen
    inventory_screen()
    print("Go To Inventory")


def achievements():
    """
    Helper method that goes to the achievement screen.

    :return: void method; Does not return anything.
    """

    from achievementsscreen import AchievementsScreen
    currentPlayer = currentUser("accounts.txt")
    achievements_screen = AchievementsScreen(currentPlayer)
    achievements_screen.run()
    print("Achievements")


def leaderboard():
    """
    Helper method that goes to the leaderboard screen.

    :return: void method; Does not return anything.
    """

    from leaderboardscreen import LeaderboardScreen
    leaderboard_screen = LeaderboardScreen(pygame.display.set_mode((900, 600)))
    leaderboard_screen.run()
    print("Leaderboard")


def tutorial():
    """
    Helper method that goes to the tutorial screen.

    :return: void method; Does not return anything.
    """
    from tutorialscreen import main
    main()

    print("Tutorial")


def admin_mode():
    """
    Helper method that goes to the admin mode screen.

    :return: void method; Does not return anything.
    """
    from adminmodescreen import AdminStatsScreen
    adminstats_screen = AdminStatsScreen(pygame.display.set_mode((900, 600)))
    adminstats_screen.run()
    print("Admin Mode")


def main_menu():
    """
    Helper method that creates the main menu screen.

    :return: void method; Does not return anything.
    """

    while True:

        SCREEN.blit(BG, (0, 0))
        MENU_MOUSE_POS = pygame.mouse.get_pos()

        text = get_font2(40)
        text_text = text.render("Welcome to", True, "Black")
        text_rect = text_text.get_rect(center=(450, 100))
        SCREEN.blit(text_text, text_rect)

        text2 = get_font2(60)
        text2_text = text2.render("Grid Genius", True, RED)
        text2_rect = text2_text.get_rect(center=(450,180))
        SCREEN.blit(text2_text, text2_rect)


        # Create buttons
        new_game_button = Button(image=button_image, pos=(460, 300), text_input="NEW GAME", font=get_font(15),
                                 base_color=GREEN, hovering_color=BRIGHT_GREEN)
        achievements_button = Button(image=button_image, pos=(460, 350), text_input="ACHIEVEMENTS", font=get_font(15),
                                     base_color=GREEN, hovering_color=BRIGHT_GREEN)
        leaderboard_button = Button(image=button_image, pos=(460, 400), text_input="LEADERBOARD", font=get_font(15),
                                    base_color=GREEN, hovering_color=BRIGHT_GREEN)
        tutorial_button = Button(image=button_image2, pos=(780, 560), text_input="TUTORIAL", font=get_font(15),
                                 base_color="Black", hovering_color=BRIGHT_GREEN)
        inventory_button = Button(image=button_image, pos=(460, 450), text_input="INVENTORY", font=get_font(15),
                                 base_color=GREEN, hovering_color=BRIGHT_GREEN)
        admin_mode_button = Button(image=button_image, pos=(145, 560), text_input="ADMIN MODE", font=get_font(15),
                                   base_color="Black", hovering_color=BRIGHT_RED)

        # Update and draw buttons
        for button in [new_game_button, achievements_button, leaderboard_button,
                       tutorial_button, admin_mode_button, inventory_button]:
            button.changeColor(MENU_MOUSE_POS)
            button.update(SCREEN)

        # Check for button input
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if new_game_button.checkForInput(MENU_MOUSE_POS):
                    new_game()
                if achievements_button.checkForInput(MENU_MOUSE_POS):
                    achievements()
                if leaderboard_button.checkForInput(MENU_MOUSE_POS):
                    leaderboard()
                if inventory_button.checkForInput(MENU_MOUSE_POS):
                    inventory()
                if admin_mode_button.checkForInput(MENU_MOUSE_POS):
                    if currentUser("accounts.txt").getUsername() == "admin":
                        admin_mode()
                if tutorial_button.checkForInput(MENU_MOUSE_POS):
                    tutorial()


        pygame.display.update()


main_menu()
