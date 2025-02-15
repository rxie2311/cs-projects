import pygame
import sys
from leaderboard import listPlayers, sortHighScore, sortAchievements
from player import Player
from button import Button

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Leaderboard')

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 200, 0)
LIGHT_GREEN = (144, 238, 144)  # Lighter green for table background
RED = (200, 0, 0)
BRIGHT_RED = (255,0,0)

# Fonts
FONT = pygame.font.Font("font.ttf", 11)
FONT1 = pygame.font.Font("font.ttf", 9)
FONT2 = pygame.font.Font("font2.ttf", 25)
FONT3 = pygame.font.Font("font2.ttf", 45)

button_image = pygame.image.load("button4.png")

top = pygame.image.load("top.png")  # Load the additional image
scaled_top = pygame.transform.scale(top, (270,270))  # Setting desired size

backdrop = pygame.image.load("backdrop.png")  # Load the additional image
scaled_backdrop = pygame.transform.scale(backdrop, (305,240))  # Setting desired size

# Load assets
BG = pygame.image.load("bg3.png")  # Ensure you have a background image named 'bg3.png'

def go_to_main_menu():
    """
    Helper method that returns to the main menu.

    :return: void method; Does not return anything.
    """

    from mainmenupage import main_menu
    main_menu()
    print("Back to main menu")
def getScreen():
    """
    Helper method that returns the screen.

    :return: void method; Does not return anything.
    """

    return SCREEN

def draw_table(screen, start_pos, title, data, col_names):
    """
    Draws a table on the screen.

    :param screen: The screen to be drawn on.
    :param start_pos: The position the table will be on.
    :param title: The title of the table.
    :param data: The data contained in the table.
    :param col_names: The names of the columns of the table.

    :return: void method; Does not return anything.
    """

    x, y = start_pos
    column_width = 150
    row_height = 30

    # Title
    title_surface = FONT.render(title, True, BLACK)
    screen.blit(title_surface, (x, y - 30))

    # Column Names
    for i, name in enumerate(col_names):
        col_surface = FONT.render(name, True, WHITE)
        screen.blit(col_surface, (x + i * column_width, y))

    # Rows
    for i, row in enumerate(data):
        for j, item in enumerate(row):
            item_surface = FONT.render(str(item), True, BLACK)
            screen.blit(item_surface, (x + j * column_width, y + (i + 1) * row_height))


class LeaderboardScreen:
    """
    The LeaderboardScreen class helps create a new leaderboard screen.
    """

    def __init__(self, screen):
        """
        Helper method that creates a new leaderboard screen.

        :param screen: The screen that will be drawn on.

        :return: void method; Does not return anything.
        """

        self.screen = screen
        self.clock = pygame.time.Clock()
        self.running = True
        self.back_button = Button(image=button_image, pos=(120, 570), text_input="Back to Main Menu", font=FONT1,
                                  base_color=GREEN,
                                  hovering_color=LIGHT_GREEN)

    def run(self):
        """
        Helper method that runs the screen when called.

        :return: void method; Does not return anything.
        """

        player_list = listPlayers("accounts.txt")
        length = min(len(player_list), 5)  # Display top 5 or fewer

        highscore_list = sortHighScore(player_list)[:length]
        achievements_list = sortAchievements(player_list)[:length]

        highscore_data = [[p.getUsername(), p.getHighScore()] for p in highscore_list]
        achievements_data = [[p.getUsername(), len(p.getAchievements()) - 1] for p in achievements_list]


        while self.running:
            keys = pygame.key.get_pressed()
            if keys[pygame.K_ESCAPE]:
                go_to_main_menu()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if self.back_button.checkForInput(pygame.mouse.get_pos()):
                        go_to_main_menu()

            SCREEN.blit(BG, (0, 0))
            SCREEN.blit(scaled_backdrop, (100, 210))
            SCREEN.blit(scaled_backdrop, (500, 210))

            highscore_text = FONT2.render("Top 5 Highscores", True, BLACK)
            achievements_text = FONT2.render("Top 5 Achievements", True, BLACK)
            title_text = FONT3.render("Leaderboard", True, RED)
            SCREEN.blit(highscore_text, (90, 170))  # Adjust position as needed
            SCREEN.blit(achievements_text, (490, 170))  # Adjust position as needed
            SCREEN.blit(title_text, (260, 60))
            SCREEN.blit(scaled_top, (290, 320))

            # Draw tables
            draw_table(self.screen, (115, 250), "", highscore_data, ["Username", "Points"])
            draw_table(self.screen, (515, 250), "", achievements_data, ["Username", "Completed"])

            mouse_pos = pygame.mouse.get_pos()
            self.back_button.changeColor(mouse_pos)
            self.back_button.update(SCREEN)

            pygame.display.flip()
            self.clock.tick(30)

        pygame.quit()
        sys.exit()


if __name__ == '__main__':
    leaderboard_screen = LeaderboardScreen(SCREEN)
    leaderboard_screen.run()
