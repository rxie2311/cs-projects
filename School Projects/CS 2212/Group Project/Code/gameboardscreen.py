import pygame
import sys
from button import Button
from questionscreen import QuestionScreen
from question import ConcreteQuestionClass
from Score import Score
from displayavatar import DisplayAvatar

# Initialize Pygame
pygame.init()

# Set up display
SCREEN = pygame.display.set_mode((900, 600))
pygame.display.set_caption('Game Board')

# Define colors
WHITE = (255, 255, 255)
GREEN = (0, 100, 0)
BRIGHT_GREEN = (0, 255, 0)
BLACK = (0, 0, 0)

# Fonts
FONT = pygame.font.Font(None, 24)

# Load assets
button_image = pygame.image.load("gamebutton.png")
BG = pygame.image.load("bg3.png")
scaled_button = pygame.transform.scale(button_image, (80, 80))
scaled_button2 = pygame.transform.scale(button_image, (190, 60))  # Adjust the size as needed
scaled_button3 = pygame.transform.scale(button_image, (200, 60))

class BaseLevelBoard:
    """
    The BaseLevelBoard method helps create a new board screen regardless of level.
    """

    def __init__(self, screen, points, level_title, subjects):
        """
        Helper method that creates a new board screen.

        :param screen: The screen that will be displayed.
        :param points: The current points that the game is at.
        :param level_title: The title of the level that the game is currently on.
        :param subjects: The subjects to be used for the board.

        :return: void method; Does not return anything.
        """

        self.screen = screen
        self.points = points
        self.level_title = level_title
        self.subjects = subjects
        self.buttons = []
        self.init_buttons()
        self.uniqueidbutton = []
        self.back_button = Button(image=scaled_button2, pos=(100, 30), text_input="Back to Main Menu", font=FONT,
                                  base_color=GREEN, hovering_color=BRIGHT_GREEN)
        self.current_score = Score()
        self.level_up = False
        self.game_over_button = Button(image=scaled_button3, pos=(200, 550), text_input="End Game",
                                       font=FONT, base_color=GREEN, hovering_color=BRIGHT_GREEN)
    def check_level_up(self):
        """
        Helper method that checks if the player's score qualifies for a level up.

        :return: int indicating the new level if a level up occurs, otherwise returns None.
        """
        score = self.current_score.getScore()
        if score >= 1000:
            return 2
        elif score >= 2000:
            return 3
        else:
            return None

    def init_buttons(self):
        """
        Helper method that creates a new button.

        :return: void method; Does not return anything.
        """

        button_width = 90
        button_height = 70
        spacing = 4
        start_x = (SCREEN.get_width() - (len(self.points[0]) * button_width + (len(self.points[0]) - 1) * spacing)) / 2
        start_y = (SCREEN.get_height() - (len(self.points) * button_height + (len(self.points) - 1) * spacing)) / 2

        for row_idx, row in enumerate(self.points):
            for col_idx, point in enumerate(row):
                x = start_x + col_idx * (button_width + spacing)
                y = start_y + row_idx * (button_height + spacing)
                button = Button(image=scaled_button, pos=(x + button_width / 2, y + button_height / 2),
                                text_input=str(point), font=FONT,
                                base_color=GREEN, hovering_color=BRIGHT_GREEN)
                self.buttons.append(button)

    def button_clicked(self, button):
        """
        Helper method that checks if a button was clicked or not.

        :param button: The button to be checked.

        :return: void method; Does not return anything.
        """

        # Find the index of the clicked button
        button_index = self.buttons.index(button)
        # Calculate the row and column index based on the button index
        row_idx = button_index // len(self.points[0])
        col_idx = button_index % len(self.points[0])
        # Fetch the corresponding subject for the clicked button
        subject = self.subjects[col_idx]  # Column determines the subject
        # Fetch the points associated with the clicked button
        points = self.points[row_idx][col_idx]
        # Update the unique ID array with the subject and points
        self.uniqueidbutton = [subject, points]
        print('Unique ID button clicked:', self.uniqueidbutton)

        clicked_values = self.uniqueidbutton
        subject = clicked_values[0]
        level = clicked_values[1]

        # Test
        questionFile = 'question.csv'
        concreteQuestion = ConcreteQuestionClass(questionFile)
        randomQuestion = concreteQuestion.generateQuestion(subject, level)

        return randomQuestion



    def run(self):
        """
        Helper method that runs the game board screen when called.

        :return: void method; Does not return anything.
        """

        question_screen = None  # This will hold the QuestionScreen instance
        done = False
        while not done:
            keys = pygame.key.get_pressed()
            if keys[pygame.K_ESCAPE]:
                from mainmenupage import main_menu
                main_menu()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    done = True
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    #mouse_pos = pygame.mouse.get_pos()
                    if self.back_button.checkForInput(mouse_pos):
                    # If the back button is clicked, return to the grid
                        self.current_score.save_score()
                        from mainmenupage import main_menu
                        main_menu()
                    elif self.game_over_button.checkForInput(mouse_pos):
                        from endGame import endGame
                        from mainmenupage import main_menu
                        endGame(self.current_score)
                        main_menu()
                    elif question_screen is None:  # Only check for button clicks if we're not showing the question
                        for button in self.buttons:
                            if button.checkForInput(pygame.mouse.get_pos()):
                                randomQuestion = self.button_clicked(button)
                                question_screen = QuestionScreen(self.screen, int(button.text_input), randomQuestion, self.current_score)
                    else:
                        # If the question screen exists, we forward the events to it
                        question_screen.handle_event(event)



            SCREEN.blit(BG, (0, 0))

            from displayavatar import DisplayAvatar
            avatarCurr = DisplayAvatar(SCREEN)
            avatarCurr.display()

            score_surface = FONT.render(f"Score: {self.current_score.getScore()}", True, BLACK)
            score_rect = score_surface.get_rect(center=(self.screen.get_width() / 2, 50))
            self.screen.blit(score_surface, score_rect)

            if self.level_up:
                level_up_surface = FONT.render("Congrats! You've leveled up", True, BLACK)
                level_up_rect = level_up_surface.get_rect(center=(self.screen.get_width() / 2, 100))
                self.screen.blit(level_up_surface, level_up_rect)

            if question_screen is None:
                # If there's no question screen, draw the buttons
                for button in self.buttons:
                    mouse_pos = pygame.mouse.get_pos()
                    button.changeColor(mouse_pos)
                    button.update(self.screen)
                    self.back_button.changeColor(mouse_pos)
                    self.back_button.update(self.screen)
                    self.game_over_button.changeColor(mouse_pos)
                    self.game_over_button.update(self.screen)
            else:
                # Otherwise, update and draw the question screen


                question_screen.update()
                question_screen.draw()

            pygame.display.flip()
            self.check_level_up()

    def check_level_up(self):
        """
        Helper method to check if the player's score meets the threshold for level up.

        :return: void method; Does not return anything.
        """

        if not self.level_up:
            if isinstance(self, Level1Board) and self.current_score.getScore() >= 1000:
                self.level_up = True
                self.expand_to_level(Level2Board)

            elif isinstance(self, Level2Board) and self.current_score.getScore() >= 2000:
                self.level_up = True
                self.expand_to_level(Level3Board)

    def expand_to_level(self, level_class):
        """
        Helper method to expand the board to the specified level.

        :param level_class: The class of the level to expand to.

        :return: void method; Does not return anything.
        """
        self.__class__ = level_class
        self.__init__(self.screen)


class Level1Board(BaseLevelBoard):
    """
    The Level1Board class determines the points and subjects of the level 1 board.
    """

    def __init__(self, screen):
        """
        Constructor that initializes the points and subjects of the level 1 board.

        :param screen: The screen that will have the board be displayed on.

        :return: void method; Does not return anything.
        """

        points = [
            [200, 200, 200],
            [400, 400, 400],
            [600, 600, 600]
        ]
        subjects = ["math", "science", "geography"]
        super().__init__(screen, points, "Level: 1", subjects)


class Level2Board(BaseLevelBoard):
    """
    The Level2Board class determines the points and subjects of the level 2 board.
    """

    def __init__(self, screen):
        """
        Constructor that initializes the points and subjects of the level 2 board.

        :param screen: The screen that will have the board be displayed on.

        :return: void method; Does not return anything.
        """

        points = [
            [200, 200, 200, 200],
            [400, 400, 400, 400],
            [600, 600, 600, 600]
        ]
        subjects = ["math", "science", "geography", "history"]
        super().__init__(screen, points, "Level: 2", subjects)


class Level3Board(BaseLevelBoard):
    """
    The Level3Board class determines the points and subjects of the level 3 board.
    """

    def __init__(self, screen):
        """
        Constructor that initializes the points and subjects of the level 3 board.

        :param screen: The screen that will have the board be displayed on.

        :return: void method; Does not return anything.
        """

        # Each subject now has an associated 200, 400, and 600 points
        points = [
            [200, 200, 200, 200, 200],
            [400, 400, 400, 400, 400],
            [600, 600, 600, 600, 600]
        ]
        subjects = ["math", "science", "geography", "history", "english"]
        super().__init__(screen, points, "Level: 3", subjects)


def main():
    """
    Helper method that runs the game board screen when called on.

    :return: void method; Does not return anything.
    """

    level = 1  # Start at level 1, adjust as needed
    board = Level1Board(SCREEN)  # Always start at level 1
    board.run()

    while True:
        board.check_level_up()  # Check for level up after each run
        board.run()

if __name__ == "__main__":
    main()
