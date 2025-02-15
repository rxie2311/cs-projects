import pygame
import sys
from button import Button
# If your login_screen function is in another file (e.g., account.py), make sure to import it
# from loginpage import login_screen

pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption("Login Page")

# Define colors
WHITE = (255, 255, 255)
GREEN = (0, 200, 0)
BRIGHT_GREEN = (0, 255, 0)
RED = (200, 0, 0)
BRIGHT_RED = (255, 0, 100)

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

button_image = pygame.image.load("button5.png")
logo = pygame.image.load("pic1.png")  # Load the additional image
scaled_logo = pygame.transform.scale(logo, (200, 200))  # Setting desired size

logo2 = pygame.image.load("pic2.png")  # Load the additional image
scaled_logo2 = pygame.transform.scale(logo2, (230, 230))  # Setting desired size

class LandingPage:
    """
    The LandingPage class helps create the landing page.
    """

    def __init__(self):
        """
        Constructor that creates a new landing page.

        :return: void method; Does not return anything.
        """

        self.running = True
        self.screen = SCREEN
        self.clock = pygame.time.Clock()
        self.login_button = Button(image=button_image, pos=(450, 480), text_input="Log In", font=get_font(15), base_color=GREEN, hovering_color=BRIGHT_GREEN)
        self.create_account_button = Button(image=button_image, pos=(450, 540), text_input="Create Account", font=get_font(15), base_color=RED, hovering_color=BRIGHT_RED)

        # Load the background image
        self.bg_image = pygame.image.load("bg3.png")

    def run(self):
        """
        Helper method that runs the landing page when called on.

        :return: void method; Does not return anything.
        """

        while self.running:

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if self.login_button.checkForInput(pygame.mouse.get_pos()):
                        self.login_action()
                    elif self.create_account_button.checkForInput(pygame.mouse.get_pos()):
                        self.create_account_action()



            # Blit the background image, other images, and text
            self.screen.blit(self.bg_image, (0, 0))
            self.screen.blit(scaled_logo, (240, 177))
            self.screen.blit(scaled_logo2, (410, 160))

            text_font = get_font2(60)
            text_text = text_font.render("Grid Genius", True, RED)
            text_rect = text_text.get_rect(topleft=(200, 100))
            SCREEN.blit(text_text, text_rect)

            text1 = get_font2(17)
            text1_text = text1.render("Big test at school?", True, "Black")
            text1_rect = text1_text.get_rect(center=(450, 50))
            SCREEN.blit(text1_text, text1_rect)

            text2 = get_font2(17)
            text2_text = text2.render("Not to worry, study with Grid Genuis!", True, "Black")
            text2_rect = text2_text.get_rect(center=(450, 70))
            SCREEN.blit(text2_text, text2_rect)

            # Update buttons
            mouse_pos = pygame.mouse.get_pos()
            self.login_button.changeColor(mouse_pos)
            self.login_button.update(self.screen)
            self.create_account_button.changeColor(mouse_pos)
            self.create_account_button.update(self.screen)

            pygame.display.update()
            self.clock.tick(60)

    def login_action(self):
        """
        Helper method that stops the landing page loop and returns to the login screen.

        :return: void method; Does not return anything.
        """

        self.running = False  # Stop the landing page loop
        from loginpagescreen import login_screen
        login_screen()  # Transition to the login screen

    def create_account_action(self):
        """
        Helper method that stops the landing page loop and goes to the account creation screen.

        :return: void method; Does not return anything.
        """

        self.running = False  # Stop the landing page loop
        from createaccountscreen import account_screen
        account_screen()

if __name__ == "__main__":
    LandingPage().run()
