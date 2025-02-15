import pygame
import sys
from button import Button  # Make sure this import works with your project structure

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((900, 600))
pygame.display.set_caption("Game Instructions")

# Load background image and define colors
bg = pygame.image.load("questionbg.png")  # Update the path as necessary
font = pygame.font.Font("font.ttf", 11)  # Adjust font size as needed
font2 = pygame.font.Font("font2.ttf", 20)  # Adjust font size as needed

# Define colors
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)  # Assuming default colors for the button
BRIGHT_GREEN = (0, 255, 0)  # Assuming default colors for the button when hovered


button_image = pygame.image.load("button5.png")  # Uncomment if using an image for the button

def draw_text(text, position, font, color="black", max_width=750):
    """
    Helper method that draws text on the screen.

    :param text: The text that shows up on the screen.
    :param position: The position of the text.
    :param font: The font of the text.
    :param color: The color of the text.
    :param max_width: The maximum width of the text.

    :return: void method; Does not return anything.
    """

    words = text.split(' ')
    x, y = position
    line = ''
    for word in words:
        test_line = line + word + ' '
        test_surface = font.render(test_line, True, color)
        if test_surface.get_width() > max_width:
            text_surface = font.render(line, True, color)
            screen.blit(text_surface, (x, y))
            line = word + ' '
            y += 20
        else:
            line = test_line
    text_surface = font.render(line, True, color)
    screen.blit(text_surface, (x, y))

def main():
    """
    Helper method that runs the tutorial screen.

    :return: void method; Does not return anything.
    """

    clock = pygame.time.Clock()
    running = True

    # Create a back button. Adjust the parameters as necessary for your design.
    back_button = Button(image=button_image, pos=(760, 50), text_input="Back to Main Menu",
                         font=font, base_color=GREEN, hovering_color=BRIGHT_GREEN)

    while running:
        screen.blit(bg, (0, 0))

        # Event handling loop
        keys = pygame.key.get_pressed()
        if keys[pygame.K_ESCAPE]:
            from mainmenupage import main_menu
            main_menu()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if back_button.checkForInput(pygame.mouse.get_pos()):
                    from mainmenupage import main_menu
                    main_menu()
                    print("Back button clicked")  # Placeholder action

        # Draw the button

        screen.blit(bg, (0, 0))


        back_button.update(screen)
        back_button.changeColor(pygame.mouse.get_pos())

        # Display the title
        title_text = "How to play:"
        title_surface = font2.render(title_text, True, "red")
        # Center the title on the screen
        screen.blit(title_surface, (20, 50))

        title_text2 = "Achievements:"
        title_surface2 = font2.render(title_text2, True, "red")
        # Center the title on the screen
        screen.blit(title_surface2, (20, 280))

        title_text2 = "Inventory:"
        title_surface2 = font2.render(title_text2, True, "red")
        # Center the title on the screen
        screen.blit(title_surface2, (20, 430))

        # Display game instructions
        instructions = """
                You will be presented with a grid of numbers. Behind each tile is a question worth the amount of points indicated by the tile. Each question will have four options that can be selected using the mouse, or the number keys 1-4. Correct answers are rewarded points while incorrect answers lead to point deductions. The goal of the game is to accumulate the most amount of points possible! As for the levels, after you reach a certain threshold of points, you are able to unlock more levels!
                """
        draw_text(instructions, (10, 100), font)

        # Display achievements
        achievements_text = """
                As you play the game, achievements are set goals that you are trying to reach. The achievements and your progress to completion can be viewed in the Achievements menu.
                """
        draw_text(achievements_text, (10, 330), font)

        # Display inventory instructions
        inventory_text = """
                As you complete achievements, inventory items will be unlocked for you to customize avatar. Each achievement has a corresponding item. Only one item can be equipped at a time.
                """
        draw_text(inventory_text, (10, 500), font)

        pygame.display.flip()
        clock.tick(30)

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()
