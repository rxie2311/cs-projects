import pygame
import sys
from button import Button

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((900, 600))
pygame.display.set_caption("Admin View Player Stats")

# Load background image and define colors
bg = pygame.image.load("bg3.png")
font = pygame.font.Font(None, 25)  # Adjust path and size as needed

# Define colors
WHITE = (255, 255, 255)
DARK_GREY = (50, 50, 50)
LIGHT_GREY = (200, 200, 200)
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

def displayStats(username):
    """
    Reads player stats from 'accounts.txt' and formats them for display.

    :return: A string of stats.
    """

    try:
        with open("accounts.txt", "r") as f:
            info = f.readlines()
            for i in range(0, len(info), 5):  # Assuming there are 5 lines per user now, including avatarID
                if info[i].split(", ")[0] == username:
                    line1 = info[i]
                    line2 = info[i + 1].strip().split(", ")
                    line3 = info[i + 2].strip().split(", ")
                    line4 = info[i + 3].strip().split(", ")  # Adjusted for achievement list
                    break
            else:  # No break means username not found
                return "Username does not exist"
    except FileNotFoundError:
        return "accounts.txt file not found"

    string = f"User: {username}\n"
    string += f"Highscore: {line2[0]}\nGames Played: {line2[1]}\nGames Won: {line2[2]}\n"
    string += "Number of Correct Answers\n"
    string += f"Math: {line3[0]}, Science: {line3[1]}, Geography: {line3[2]}, History: {line3[3]}, English: {line3[4]}\n"
    achievements = ", ".join(line4) if line4 != ["0"] else "None"
    string += f"Achievements Unlocked: {achievements}"
    return string


def draw_text(text, position, font, color="Black"):
    """
    Draws text on the screen, managing vertical space for sequential blocks.

    :return: The y coordinate after the last line.
    """

    x, y = position
    for line in text.split('\n'):  # Split the text into lines
        text_surface = font.render(line, True, color)
        screen.blit(text_surface, (x, y))
        y += 30  # Add vertical space for the next line
    return y  # Return the Y coordinate after the last line


def main():
    """
    Helper method to run the admin view command.

    :return: void method; Does not return anything.
    """

    input_text = ''  # For user input
    stats_display = ''  # To store stats for display
    input_active = False  # To track input box state
    input_box = pygame.Rect(100, 50, 140, 32)
    color_inactive = DARK_GREY
    color_active = LIGHT_GREY
    input_box_color = color_inactive

    back_button = Button(image=button_image, pos=(650, 560), text_input="GO BACK", font=font, base_color="Black",
                         hovering_color="green")

    clock = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                input_active = input_box.collidepoint(event.pos)
                input_box_color = color_active if input_active else color_inactive
                if back_button.checkForInput(pygame.mouse.get_pos()):
                        go_back()
            if event.type == pygame.KEYDOWN and input_active:
                if event.key == pygame.K_RETURN:
                    stats_display = displayStats(input_text)  # Fetch and display stats
                    input_text = ''  # Clear input text after displaying stats
                elif event.key == pygame.K_BACKSPACE:
                    input_text = input_text[:-1]
                else:
                    input_text += event.unicode

        screen.blit(bg, (0, 0))
        txt_surface = font.render(input_text, True, WHITE)

        back_button.changeColor(pygame.mouse.get_pos())
        back_button.update(screen)

        instruction_text_surface = font.render("Enter username and press ENTER to view details", True, "Black")
        screen.blit(instruction_text_surface, (input_box.x, input_box.y - 30))

        width = max(200, txt_surface.get_width() + 10)
        input_box.w = width
        screen.blit(txt_surface, (input_box.x + 5, input_box.y + 5))
        pygame.draw.rect(screen, input_box_color, input_box, 2)

        if stats_display:
            draw_text(stats_display, (10, 100), font)

        pygame.display.flip()
        clock.tick(30)


if __name__ == "__main__":
    main()
