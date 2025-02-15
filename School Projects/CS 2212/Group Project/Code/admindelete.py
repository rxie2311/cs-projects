import pygame
import sys
from account import deleteAccount  # Make sure account.py is in the same directory
from button import Button

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 200, 0)
LIGHT_GREY = (200, 200, 200)
LIGHT_GREEN = (144, 238, 144)
RED = (200, 0, 0)
BRIGHT_GREEN = (0, 255, 0)
DARK_GREY = (50, 50, 50)
BRIGHT_RED = (255, 0, 0)

BG = pygame.image.load("bg3.png")

pygame.init()
screen = pygame.display.set_mode((900, 600))
pygame.display.set_caption("Admin Delete Player Profile")

font = pygame.font.Font("font.ttf", 11)
input_box_color = pygame.Color('#FFE7F3')
input_box_active_color = pygame.Color(WHITE)
button_color = pygame.Color(WHITE)
button_hover_color = pygame.Color('lightskyblue3')
text_color = pygame.Color(BLACK)

button_image = pygame.image.load("button4.png")

def go_back():
    """
    Helper method to go back a screen.

    :return: void method; Does not return anything.
    """

    from adminmodescreen import AdminStatsScreen
    adminstats_screen = AdminStatsScreen(screen)
    adminstats_screen.run()
    print("Back to Options")

def draw_text(text, position, color=text_color, font=font):
    """
    Utility function to draw text on the screen.

    :param text: The text for the menu.
    :param position: The position of the text.
    :param color: The color of the text.
    :param font: The font of the text.

    :return: void method; Does not return anything.
    """

    surface = font.render(text, True, color)
    screen.blit(surface, position)

def main():
    """
    Helper method to run the admin delete command.

    :return: void method; Does not return anything.
    """

    clock = pygame.time.Clock()
    input_box = pygame.Rect(100, 100, 200, 30)
    input_text = ""
    active_box = False
    delete_button = pygame.Rect(100, 500, 120, 40)
    button_pressed = False

    back_button = Button(image=button_image, pos=(650, 560), text_input="GO BACK", font=font, base_color="Black", hovering_color="green")

    done = False
    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            if event.type == pygame.MOUSEBUTTONDOWN:
                if delete_button.collidepoint(event.pos):
                    button_pressed = True
                    # Call the delete user function
                    if deleteAccount("accounts.txt", input_text):
                        print(f"User {input_text} deleted successfully.")
                    else:
                        print(f"Failed to delete {input_text}. User not found.")
                elif back_button.checkForInput(pygame.mouse.get_pos()):
                        go_back()
                else:
                    button_pressed = False
                active_box = input_box.collidepoint(event.pos)
            if event.type == pygame.KEYDOWN and active_box:
                if event.key == pygame.K_BACKSPACE:
                    input_text = input_text[:-1]
                else:
                    input_text += event.unicode

        screen.blit(BG, (0, 0))
        pygame.draw.rect(screen, input_box_active_color if active_box else input_box_color, input_box)
        draw_text(input_text, (input_box.x + 5, input_box.y + 5))

        draw_text("Username:", (input_box.x, input_box.y - 30), text_color)

        # Delete button
        mouse_pos = pygame.mouse.get_pos()
        button_hover = delete_button.collidepoint(mouse_pos)
        pygame.draw.rect(screen, button_hover_color if button_hover or button_pressed else button_color, delete_button)
        draw_text("Delete", (delete_button.x + 35, delete_button.y + 5), BLACK)

        back_button.changeColor(mouse_pos)
        back_button.update(screen)

        pygame.display.flip()
        clock.tick(30)

    pygame.quit()
    sys.exit()

if __name__ == '__main__':
    main()
