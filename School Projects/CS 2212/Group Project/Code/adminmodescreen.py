import pygame
import sys
from admincommands import displayStats, displayUsernames
from account import deleteAccount
from button import Button

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Admin Stats')

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 200, 0)
LIGHT_GREY = (200, 200, 200)
LIGHT_GREEN = (144, 238, 144)  # Lighter green for table background
RED = (200, 0, 0)
BRIGHT_GREEN = (0, 255, 0)
DARK_GREY = (50, 50, 50)
BRIGHT_RED = (255, 0, 0)

# Fonts
FONT = pygame.font.Font("font.ttf", 11)
FONT1 = pygame.font.Font("font.ttf", 9)
FONT2 = pygame.font.Font("font2.ttf", 25)
FONT3 = pygame.font.Font("font2.ttf", 45)

button_image = pygame.image.load("button4.png")
backdrop = pygame.image.load("backdrop.png")  # Load the additional image
scaled_backdrop = pygame.transform.scale(backdrop, (305, 240))  # Setting desired size

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

def admin_edit():
    """
    Helper method that goes to the admin edit screen.

    :return: void method; Does not return anything.
    """

    print("Switching to Admin Edit Screen...")  # Replace with actual admin_edit logic
    from adminedit import main
    main()

def admin_delete():
    """
    Helper method that goes to the admin delete screen.

    :return: void method; Does not return anything.
    """

    print("Switching to Admin Delete Screen...")  # Replace with actual admin_delete logic
    from admindelete import main
    main()

def admin_view():
    """
    Helper method that goes to the admin view screen.

    :return: void method; Does not return anything.
    """

    print("Switching to Admin View Screen...")  # Replace with actual admin_view logic
    from adminview import main
    main()
    # admin_view logic here...

def admin_add_question():
    """
    Helper method that goes to the admin add question screen.

    :return: void method; Does not return anything.
    """

    print("Switching to Admin Add Question Screen...")  # Replace with actual admin_add_question logic
    # admin_add_question logic here...

def getScreen():
    """
    Helper method that returns the screen.

    :return: Returns the screen.
    """

    return SCREEN

def draw_table(screen, start_pos, title, data, col_names):
    """
    Helper method that draws a table.

    :param screen: The screen the table will be displayed on.
    :param start_pos: The starting position of the table.
    :param title: The title of the table.
    :param data: The data stored in the table.
    :param col_names: The names of the columns.

    :return: void method; Does not return anything.
    """

    x, y = start_pos
    column_width = 25
    row_height = 20

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

class InputBox:
    """
    The InputBox class creates a text box for user input.
    """

    def __init__(self, x, y, w, h, text=''):
        """
        Constructor to make a new input box.

        :param x: The x-coordinate of the box.
        :param y: The y-coordinate of the box.
        :param w: The width of the box.
        :param h: The height of the box.
        :param text: The text in the box.

        :return: void method; Does not return anything.
        """

        self.rect = pygame.Rect(x, y, w, h)
        self.color = LIGHT_GREY
        self.text = text
        self.txt_surface = FONT.render(text, True, self.color)
        self.active = False

    def handle_event(self, event):
        """
        Helper method that handles when the input box is interacted with.

        :param event: The event that occurred in the input box.

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
                self.txt_surface = FONT.render(self.text, True, BLACK)

    def update(self):
        """
        Helper method that updates the input box if needed.

        :return: void method; Does not return anything.
        """

        width = max(200, self.txt_surface.get_width() + 10)
        self.rect.w = width

    def draw(self, screen):
        """
        Helper method that draws the input box on the screen.

        :param screen: The screen that the input box will be drawn on.

        :return: void method; Does not return anything.
        """

        pygame.draw.rect(screen, WHITE, self.rect)
        screen.blit(self.txt_surface, (self.rect.x + 5, self.rect.y + 5))
        pygame.draw.rect(screen, self.color, self.rect, 2)

class AdminStatsScreen:
    """
    The AdminStatsScreen class creates the admin stats screen.
    """

    def __init__(self, screen):
        """
        Constructor creates a new AdminStatsScreen.

        :param screen: The screen that will be drawn on.

        :return: void method; Does not return anything.
        """

        self.screen = screen
        self.clock = pygame.time.Clock()
        self.running = True
        self.back_button = Button(image=button_image, pos=(120, 570), text_input="Back to Main Menu", font=FONT1, base_color=GREEN, hovering_color=LIGHT_GREY)
        # Define buttons for options
        self.edit_user_button = Button(image=button_image, pos=(650, 250), text_input="Edit User", font=FONT1, base_color=GREEN, hovering_color=LIGHT_GREEN)
        self.delete_user_button = Button(image=button_image, pos=(650, 300), text_input="Delete User", font=FONT1, base_color=GREEN, hovering_color=LIGHT_GREEN)
        self.view_user_button = Button(image=button_image, pos=(650, 350), text_input="View User", font=FONT1, base_color=GREEN, hovering_color=LIGHT_GREEN)
        self.add_question_button = Button(image=button_image, pos=(650, 400), text_input="Add Question", font=FONT1, base_color=GREEN, hovering_color=LIGHT_GREEN)

    def run(self):
        """
        Helper method that runs the screen.

        :return: void method; Does not return anything.
        """

        username_list = displayUsernames()

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
                    elif self.edit_user_button.checkForInput(pygame.mouse.get_pos()):
                        admin_edit()
                    elif self.delete_user_button.checkForInput(pygame.mouse.get_pos()):
                        admin_delete()
                    elif self.view_user_button.checkForInput(pygame.mouse.get_pos()):
                        admin_view()
                    elif self.add_question_button.checkForInput(pygame.mouse.get_pos()):
                        print("hi")

            SCREEN.blit(BG, (0, 0))
            SCREEN.blit(scaled_backdrop, (100, 210))
            SCREEN.blit(scaled_backdrop, (500, 210))

            username_text = FONT2.render("All Users", True, BLACK)
            options_text = FONT2.render("Options", True, BLACK)
            title_text = FONT3.render("Admin Mode", True, RED)
            SCREEN.blit(username_text, (150, 170))
            SCREEN.blit(options_text, (560, 170))
            SCREEN.blit(title_text, (260, 60))

            draw_table(self.screen, (115, 250), "Usernames", username_list, [""])

            # Update and draw buttons
            mouse_pos = pygame.mouse.get_pos()

            self.back_button.changeColor(mouse_pos)
            self.back_button.update(SCREEN)

            self.edit_user_button.changeColor(mouse_pos)
            self.edit_user_button.update(SCREEN)

            self.delete_user_button.changeColor(mouse_pos)
            self.delete_user_button.update(SCREEN)

            self.view_user_button.changeColor(mouse_pos)
            self.view_user_button.update(SCREEN)

            #self.add_question_button.changeColor(mouse_pos)
            #self.add_question_button.update(SCREEN)


            pygame.display.flip()
            self.clock.tick(30)

        pygame.quit()
        sys.exit()

if __name__ == '__main__':
    adminstats_screen = AdminStatsScreen(SCREEN)
    adminstats_screen.run()
