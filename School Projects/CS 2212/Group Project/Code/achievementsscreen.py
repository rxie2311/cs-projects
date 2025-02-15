import pygame
import sys
from achievements import checkAchievements, displayProgress, isDone
from player import currentUser
from button import Button

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Achievements')

# Define colors and fonts
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 200, 0)
RED = (200, 0, 0)
BRIGHT_GREEN = (0, 255, 0)

FONT = pygame.font.Font("font.ttf", 9)
FONT2 = pygame.font.Font("font2.ttf", 40)
FONT3 = pygame.font.Font("font.ttf", 9)

# Load assets
BG = pygame.image.load("bg3.png")
button_image = pygame.image.load("button4.png")
backdrop = pygame.image.load("backdrop.png")
scaled_backdrop = pygame.transform.scale(backdrop, (740, 350))

girl = pygame.image.load("happygirl.png")  # Load the additional image
scaled_girl = pygame.transform.scale(girl, (210,210))  # Setting desired size

correct_image_original = pygame.image.load("correct.png")
incorrect_image_original = pygame.image.load("incorrect.png")
# Scale completion status images to 10x10
correct_image = pygame.transform.scale(correct_image_original, (30, 30))
incorrect_image = pygame.transform.scale(incorrect_image_original, (30, 30))

# Achievements descriptions
achievement_descriptions = {
    1: "Complete 10 games",
    2: "Win 10 games",
    3: "Get a high score of 10,000",
    4: "Answer 20 math questions correctly",
    5: "Answer 20 science questions correctly",
    6: "Answer 20 geography questions correctly",
    7: "Answer 20 history questions correctly",
    8: "Answer 20 english questions correctly",
    9: "Complete all achievements"
}

def go_to_main_menu():
    """
    Helper method that returns to the main menu

    :return: void method; Does not return anything.
    """

    from mainmenupage import main_menu
    main_menu()
    print("Back to main menu")

class AchievementsScreen:
    """
    The AchievementsScreen class helps create a screen for the achievements tab in the game.
    """

    def __init__(self, player):
        """
        Constructor that creates the achievement screen.

        :param player: The player profile that the screen will show statistics of achievements of.

        :return: void method; Does not return anything.
        """

        self.running = True
        self.player = player
        self.clock = pygame.time.Clock()
        self.back_button = Button(image=button_image, pos=(110, 570), text_input="Back to Main Menu", font=FONT, base_color=GREEN, hovering_color=BRIGHT_GREEN)

    def draw_text(self, text, font, position, color=BLACK):
        """
        Helper method that draws the text on the screen.

        :param text: Text on the screen.
        :param font: Font for the text on the screen.
        :param position: Position that the text will be in on the screen.
        :param color: Color of the text.

        :return: void method; Does not return anything.
        """

        text_surface = font.render(text, True, color)
        text_rect = text_surface.get_rect(topleft=position)
        SCREEN.blit(text_surface, text_rect)

    def run(self):
        """
        Helper method that runs the screen when called.

        :return: void method; Does not return anything.
        """

        checkAchievements(self.player)  # Update achievements status
        while self.running:
            SCREEN.blit(BG, (0, 0))
            SCREEN.blit(scaled_backdrop, (80, 110))
            SCREEN.blit(scaled_girl, (710, 410))

            self.draw_text("Achievements", FONT2, (260, 50), RED)

            # Column titles
            column_titles = ["Achievement", "Description", "Progress", "Completion"]
            column_start_x = [100, 220, 600, 700]  # X positions for each column
            y_offset = 130  # Start y position for column titles
            for i, title in enumerate(column_titles):
                self.draw_text(title, FONT3, (column_start_x[i], y_offset), BLACK)

            y_offset += 40  # Adjust y_offset for the rows
            for i in range(1, 10):  # Assuming 9 achievements
                description = achievement_descriptions[i]
                progress = displayProgress(self.player, i)
                completion_image = correct_image if isDone(self.player, i) else incorrect_image

                # Achievement Number
                self.draw_text(str(i), FONT3, (column_start_x[0], y_offset))
                # Description
                self.draw_text(description, FONT3, (column_start_x[1], y_offset))
                # Progress
                self.draw_text(progress, FONT3, (column_start_x[2], y_offset))
                # Completion Image
                SCREEN.blit(completion_image, (column_start_x[3], y_offset-12))

                y_offset += 30  # Move to the next row for entries

            keys = pygame.key.get_pressed()
            if keys[pygame.K_ESCAPE]:
                go_to_main_menu()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if self.back_button.checkForInput(pygame.mouse.get_pos()):
                        go_to_main_menu()

            mouse_pos = pygame.mouse.get_pos()
            self.back_button.changeColor(mouse_pos)
            self.back_button.update(SCREEN)

            pygame.display.flip()
            self.clock.tick(30)

        pygame.quit()
        sys.exit()

player = currentUser("accounts.txt")

if __name__ == '__main__':
    achievements_screen = AchievementsScreen(player)
    achievements_screen.run()