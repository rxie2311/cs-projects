import pygame
import sys
from button import Button
from account import *

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Create Account')

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
LIGHT_GREY = (200, 200, 200)
DARK_GREY = (50, 50, 50)
GREEN = (0, 200, 0)
BRIGHT_GREEN = (0, 255, 0)
RED = (200, 0, 0)
BRIGHT_RED = (255, 0, 100)

# Fonts
FONT = pygame.font.Font("font.ttf", 10)
FONT2 = pygame.font.Font("font.ttf", 9)
FONT3 = pygame.font.Font("font2.ttf", 18)
BG = pygame.image.load("bg3.png")  # Background image
button_image = pygame.image.load("button4.png")

backdrop = pygame.image.load("backdrop.png")  # Load the additional image
scaled_backdrop = pygame.transform.scale(backdrop, (400, 300))  # Setting desired size

pic = pygame.image.load("pic1.png")  # Load the additional image
scaled_pic = pygame.transform.scale(pic, (200, 200))  # Setting desired size


class InputBox:
    """
    The InputBox method helps create a text box for the user to type in.
    """

    def __init__(self, x, y, w, h, text=''):
        """
        Constructor that creates the new text box.

        :param x: The x-coordinate of the box location.
        :param y: The y-coordinate of the box location.
        :param w: The width of the text box.
        :param h: The height of the text box.
        :param text: The text inside the box.

        :return: void method; Does not return anything.
        """

        self.rect = pygame.Rect(x, y, w, h)
        self.color = LIGHT_GREY
        self.text = text
        self.txt_surface = FONT.render(text, True, self.color)
        self.active = False

    def handle_event(self, event):
        """
        Helper method that handles when the text box is interacted with.

        :param event: The interaction with the text box (mouse button click, keyboard key press).

        :return: void method; Does not return anything.
        """

        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.rect.collidepoint(event.pos):
                self.active = not self.active
            else:
                self.active = False
            self.color = DARK_GREY if self.active else LIGHT_GREY
        if event.type == pygame.KEYDOWN:
            if self.active:
                if event.key == pygame.K_RETURN:
                    print(self.text)
                    self.text = ''
                elif event.key == pygame.K_BACKSPACE:
                    self.text = self.text[:-1]
                else:
                    self.text += event.unicode
                # Re-render the text
                self.txt_surface = FONT.render(self.text, True, BLACK)

    def update(self):
        """
        Helper method that resizes the box if the text is too large.

        :return: void method; Does not return anything.
        """

        # Resize the box if the text is too long.
        width = max(200, self.txt_surface.get_width() + 10)
        self.rect.w = width

    def draw(self, screen):
        """
        Helper method that changes the color of the screen.

        :param screen: The screen that needs to change color.

        :return: void method; Does not return anything.
        """

        # Fill the box with white color
        pygame.draw.rect(screen, WHITE, self.rect)
        # Blit the text.
        screen.blit(self.txt_surface, (self.rect.x + 5, self.rect.y + 5))
        # Blit the rect.
        pygame.draw.rect(screen, self.color, self.rect, 2)


# Function to get the desired font
def get_font(size):
    """
    Helper method that returns the font.

    :param size: The size of the font.

    :return: The font of the text.
    """

    return FONT

def get_font2(size):
    """
    Helper method that returns the second font.

    :param size: The size of the font.

    :return: The second font of the text.
    """

    return FONT3

def go_to_login_page():
    """
    Helper method that returns to the login page.

    :return: void method; Does not return anything.
    """

    from loginpagescreen import login_screen
    login_screen()
    print("Redirecting to login page")

def account_screen():
    """
    Helper method that runs the account screen when called.

    :return: void method; Does not return anything.
    """

    new_username_box = InputBox(400, 200, 140, 32)
    new_password_box = InputBox(400, 250, 140, 32)
    input_boxes = [new_username_box, new_password_box]
    account_button = Button(image=button_image, pos=(450, 350), text_input="CREATE ACCOUNT", font=FONT,
                            base_color=GREEN,
                            hovering_color=BRIGHT_GREEN)
    go_to_login_button = Button(image=button_image, pos=(750, 550), text_input="GO TO LOGIN", font=FONT,
                                base_color=GREEN, hovering_color=BRIGHT_GREEN)

    done = False

    while not done:

        SCREEN.blit(BG, (0, 0))

        SCREEN.blit(scaled_backdrop, (240, 110))

        SCREEN.blit(scaled_pic, (340, 5))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            for box in input_boxes:
                box.handle_event(event)
            if event.type == pygame.MOUSEBUTTONDOWN:
                if account_button.checkForInput(pygame.mouse.get_pos()):
                    # Here you can handle the login functionality
                    user_data = [new_username_box.text, new_password_box.text]
                    createAccount("accounts.txt", user_data[0], user_data[1])
                    #title2_text = FONT2.render("Account created Successfully! Log In", True, "Black")
                    #SCREEN.blit(title2_text, (200, 120))

                elif go_to_login_button.checkForInput(mouse_pos):
                    go_to_login_page()

        for box in input_boxes:
            box.update()


        text1_font = get_font2(16)
        text1_text = text1_font.render("Username: ", True, BLACK)
        text1_rect = text1_text.get_rect(center=(340, 215))
        SCREEN.blit(text1_text, text1_rect)

        text2_font = get_font2(16)
        text2_text = text2_font.render("Password: ", True, BLACK)
        text2_rect = text2_text.get_rect(center=(340, 265))
        SCREEN.blit(text2_text, text2_rect)

        for box in input_boxes:
            box.draw(SCREEN)

        mouse_pos = pygame.mouse.get_pos()

        account_button.changeColor(mouse_pos)
        account_button.update(SCREEN)

        go_to_login_button.changeColor(mouse_pos)
        go_to_login_button.update(SCREEN)


        pygame.display.flip()

    pygame.quit()
    sys.exit()


account_screen()
