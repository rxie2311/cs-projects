import pygame
import sys
from button import Button
from account import *

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Login Page')

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
FONT = pygame.font.Font("font.ttf", 15)
FONT3 = pygame.font.Font("font2.ttf", 18)
BG = pygame.image.load("bg3.png")  # Background image
button_image = pygame.image.load("button4.png")

backdrop = pygame.image.load("backdrop.png")  # Load the additional image
scaled_backdrop = pygame.transform.scale(backdrop, (400, 300))  # Setting desired size

pic = pygame.image.load("pic2.png")  # Load the additional image
scaled_pic = pygame.transform.scale(pic, (200, 200))  # Setting desired size

def go_to_main_menu():
    """
    Helper method that goes to the main menu page.

    :return: void method; Does not return anything.
    """

    from mainmenupage import main_menu
    main_menu()
    print("Back to main menu")

class InputBox:
    """
    The InputBox class is used to generate a text box.
    """

    def __init__(self, x, y, w, h, text=''):
        """
        Constructor used to generate the text box for the login page

        :param x: int; x-coordinate for the rectangle.
        :param y: int; y-coordinate for the rectangle.
        :param w: int; width of the rectangle.
        :param h: int; height of the rectangle.
        :param text: String; The text that shows in the text box.

        :return: void method; Does not return anything.
        """

        # Creating the login page text box
        self.rect = pygame.Rect(x, y, w, h)
        self.color = LIGHT_GREY
        self.text = text
        self.txt_surface = FONT.render(text, True, self.color)
        self.active = False

    def handle_event(self, event):
        """
        Helper method that handles when a mouse button click and a keyboard key press is done on the text box.

        :param event: Detects an interaction (mouse click)

        :return: void method; Does not return anything.
        """

        # Checks for a mouse click
        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.rect.collidepoint(event.pos):
                self.active = not self.active
            else:
                self.active = False
            self.color = DARK_GREY if self.active else LIGHT_GREY
        # Checks for if a key is pressed
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
        Helper method that resizes the text box if it is too small.

        :return: void method; Does not return anything.
        """

        # Resize the box if the text is too long.
        width = max(200, self.txt_surface.get_width() + 10)
        self.rect.w = width

    def draw(self, screen):
        # Fill the box with white color
        pygame.draw.rect(screen, WHITE, self.rect)
        # Blit the text.
        screen.blit(self.txt_surface, (self.rect.x + 5, self.rect.y + 5))
        # Blit the rect.
        pygame.draw.rect(screen, self.color, self.rect, 2)

def get_font(size):
    """
    Helper method to return font.

    :return: Returns the text font.
    """
    return FONT

def get_font2(size):
    return FONT3

def login_screen():
    """
    Helper method that creates a login screen GUI.

    :return: void method; Does not return anything.
    """

    username_box = InputBox(400, 200, 140, 32)
    password_box = InputBox(400, 250, 140, 32)
    input_boxes = [username_box, password_box]
    login_button = Button(image=button_image, pos=(450, 350), text_input="LOGIN", font=FONT, base_color=GREEN,
                          hovering_color=BRIGHT_GREEN)

    done = False

    while not done:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            for box in input_boxes:
                box.handle_event(event)
            if event.type == pygame.MOUSEBUTTONDOWN:
                if login_button.checkForInput(pygame.mouse.get_pos()):
                    # Here you can handle the login functionality
                    user_data = [username_box.text, password_box.text]
                    corrLogIn = login("accounts.txt", user_data[0], user_data[1])
                    if corrLogIn:
                        print("Successfully logged in, welcome back!")
                        go_to_main_menu() # Call the main menu or login function
                    else:
                        print("Incorrect username or password.")
        for box in input_boxes:
            box.update()

        SCREEN.blit(BG, (0, 0))

        SCREEN.blit(scaled_backdrop, (240, 110))

        SCREEN.blit(scaled_pic, (340, 5))

        text1_font = get_font2(23)
        text1_text = text1_font.render("Username: ", True, BLACK)
        text1_rect = text1_text.get_rect(center=(340, 215))
        SCREEN.blit(text1_text, text1_rect)

        text2_font = get_font2(23)
        text2_text = text2_font.render("Password: ", True, BLACK)
        text2_rect = text2_text.get_rect(center=(340, 265))
        SCREEN.blit(text2_text, text2_rect)

        for box in input_boxes:
            box.draw(SCREEN)

        mouse_pos = pygame.mouse.get_pos()
        login_button.changeColor(mouse_pos)
        login_button.update(SCREEN)

        pygame.display.flip()

    # Quits out of pygame and exits the GUI
    pygame.quit()
    sys.exit()

login_screen()
