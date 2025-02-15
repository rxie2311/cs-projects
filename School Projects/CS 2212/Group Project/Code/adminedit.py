import pygame
import sys
from edituser import load_players, save_players, update_player, get_player
from button import Button

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


BG = pygame.image.load("bg3.png")

pygame.init()
screen = pygame.display.set_mode((900, 600))
pygame.display.set_caption("Admin Edit Player Profile")

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

def draw_button(text, rect, active):
    """
    Utility function to draw buttons on the screen.

    :param text: The text for the button.
    :param rect: The rectangle size of the button.
    :param active: If the button is active or not.

    :return: void method; Does not return anything.
    """

    pygame.draw.rect(screen, button_hover_color if active else button_color, rect)
    draw_text(text, (rect.x + 20, rect.y + 5), text_color)

def main():
    """
    Helper method to run the admin edit command.

    :return: void method; Does not return anything.
    """

    clock = pygame.time.Clock()
    input_boxes = [pygame.Rect(100, 100 + 100 * i, 200, 30) for i in range(4)]
    inputs = [""] * len(input_boxes)
    active_boxes = [False] * len(input_boxes)
    labels = ["Username:", "High Score:", "Add Achievements:", "Remove Achievements:"]
    update_button = pygame.Rect(100, 500, 120, 40)
    button_pressed = False

    back_button = Button(image=button_image, pos=(650, 560), text_input="GO BACK", font=font, base_color="Black", hovering_color="green")

    done = False
    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            if event.type == pygame.MOUSEBUTTONDOWN:
                if update_button.collidepoint(event.pos):
                    button_pressed = True
                    # Process update here
                    username = inputs[0]
                    high_score = inputs[1] if inputs[1].isdigit() else None
                    achievements_add = list(map(int, inputs[2].split(','))) if inputs[2] else None
                    achievements_remove = list(map(int, inputs[3].split(','))) if inputs[3] else None
                    players = load_players()
                    if update_player(players, username, high_score, achievements_add, achievements_remove):
                        save_players(players)
                        print(f"Profile updated for {username}")
                    else:
                        print(f"Player {username} not found.")
                elif back_button.checkForInput(mouse_pos):
                        go_back()
                else:
                    button_pressed = False
                for i, box in enumerate(input_boxes):
                    active_boxes[i] = box.collidepoint(event.pos)
            if event.type == pygame.KEYDOWN:
                for i, active in enumerate(active_boxes):
                    if active:
                        if event.key == pygame.K_BACKSPACE:
                            inputs[i] = inputs[i][:-1]
                        else:
                            inputs[i] += event.unicode

        screen.blit(BG, (0, 0))

        for i, box in enumerate(input_boxes):
            pygame.draw.rect(screen, input_box_active_color if active_boxes[i] else input_box_color, box)
            draw_text(inputs[i], (box.x + 5, box.y + 5))
            draw_text(labels[i], (box.x, box.y - 30), text_color)

        # Update button
        mouse_pos = pygame.mouse.get_pos()
        button_hover = update_button.collidepoint(mouse_pos)
        draw_button("Update", update_button, button_hover or button_pressed)

        for button in [back_button]:
            button.changeColor(mouse_pos)
            button.update(screen)

        pygame.display.flip()
        clock.tick(30)

    pygame.quit()
    sys.exit()

if __name__ == '__main__':
    main()
