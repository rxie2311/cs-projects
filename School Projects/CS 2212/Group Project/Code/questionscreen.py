
import pygame
import sys
from question import ConcreteQuestionClass
from Score import Score
# Initialize Pygame
pygame.init()

# Fonts
FONT = pygame.font.Font("font.ttf", 12)
FONT4 = pygame.font.Font(None, 25)


# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 150, 0)
BRIGHT_GREEN = (0, 255, 0)
button_image = pygame.image.load("button3.png")
BG = pygame.image.load("questionbg.png")
speech_bubble_image = pygame.image.load("speechbubble.png")

from button import Button

def go_to_grid():
    from mainmenupage import new_game
    new_game()
class QuestionScreen:
    """
    The QuestionScreen class creates a new question screen when the user clicks on a question in game.
    """

    def __init__(self, screen, points, randomQuestion, score):
        """
        Constructor that creates a new question screen.

        :param screen: The screen to be written on.
        :param points: The current points to display on the screen.
        :param randomQuestion: The question that will be selected from the file.

        :return: void method; Does not return anything.
        """

        self.screen = screen
        self.points = points
        self.randomQuestion = randomQuestion
        if randomQuestion is not None:
            self.question_text, self.options = self.parse_question(randomQuestion.questionStr)
            self.answer_text = randomQuestion.answerStr
        else:
            self.question_text = "No question available"
            self.options = ["No options"]
        self.buttons = []
        self.init_buttons()
        self.feedback_text = ""
        self.back_button2 = Button(image=button_image, pos=(100, 30), text_input="Back to Game", font=FONT,
                                  base_color=GREEN, hovering_color=BRIGHT_GREEN)
        self.score = score  # Pass the Score object
        self.answered_correctly = False

    def check_answer(self, clicked_option):
        option_parts = clicked_option.split(':')

        # Check if there are at least two parts after splitting
        if len(option_parts) >= 2:
            # Extract the last part which should be the answer
            answer = option_parts[-1].strip()

            # Now you have the answer, compare it with the correct answer
            if getattr(self, 'randomQuestion', None) is not None and answer == self.randomQuestion.answerStr:
                self.feedback_text = "Correct answer!"
                self.score.increase_questionCount(self.randomQuestion.subject)
                self.score.updateScore(self.randomQuestion.questionPoints)  # Update the score
                self.answered_correctly = True
                for button in self.buttons:
                    button.disabled = True
            else:
                self.feedback_text = "Incorrect answer!"
                self.score.updateNegScore(self.randomQuestion.questionPoints)

                self.screen.blit(speech_bubble_image, (5, 5))

                # tutorial text on top of the speech bubble
                tutorial_font = pygame.font.Font("font.ttf", 14)
                tutorial_text = self.randomQuestion.tutorial
                tutorial_surface = tutorial_font.render(tutorial_text, True, BLACK)
                tutorial_rect = tutorial_surface.get_rect(center=(200 + speech_bubble_image.get_width() / 2, 300 + speech_bubble_image.get_height() / 2))

                # Debugging output
                print(f"Tutorial Text: {self.randomQuestion.tutorial}")
                print(f"Tutorial Surface Size: {tutorial_surface.get_size()}")
                print(f"Tutorial Rect: {tutorial_rect}")

                # Blit tutorial text onto the screen
                self.screen.blit(tutorial_surface, tutorial_rect)

    def parse_question(self, question_str):
        """
        Helper method that splits up the chosen question from the file.

        :param question_str: The question that was chosen from the file.

        :return: The question and the multiple choice options.
        """

        # Split the question string based on the '=' character to separate the question from the options
        question_parts = question_str.split('?')
        # The question is the first part before the '=' character
        question = question_parts[0].strip()
        # The options are the second part after the '=' character
        options = [opt.strip() for opt in question_parts[1].split('\n') if opt.strip()]
        return question, options

    def init_buttons(self):
        """
        Constructor that creates a new button.

        :return: void method; Does not return anything.
        """

        button_width = 400
        button_height = 50
        spacing = 20
        start_x = (self.screen.get_width() - button_width) / 2
        start_y = 200  # Starting Y position for the option buttons

        for i, option in enumerate(self.options):
            button = Button(image=None, pos=(start_x + button_width / 2, start_y + i * (button_height + spacing)),
                            text_input=option, font=FONT, base_color=GREEN, hovering_color=BRIGHT_GREEN)
            self.buttons.append(button)

    def handle_event(self, event):
        """
        Helper method that checks if the button has been interacted with.

        :param event: The interaction that has been done to the button.

        :return: void method; Does not return anything.
        """

        if event.type == pygame.MOUSEBUTTONDOWN:
            mouse_pos = pygame.mouse.get_pos()
            if self.back_button2.checkForInput(mouse_pos):
                go_to_grid()
                self.done = True  # Assuming you're using a loop control flag
            elif not self.answered_correctly:  # Check if the question has not been answered correctly yet
                for button in self.buttons:
                    if button.checkForInput(mouse_pos):
                        clicked_option = button.text_input
                        print(f"{button.text_input} has been clicked")
                        self.check_answer(clicked_option)


    def update(self):
        """
        Helper method that updates the screen if necessary.

        :return: void method; Does not return anything.
        """

        # This function would contain any logic to update the screen elements
        pass


    def draw_text(self, text, position, font, color=(0, 0, 0), max_width=None):
        """
        Draw text on the screen with optional text wrapping.
        """
        words = text.split(' ')
        lines = []
        current_line = ''
        for word in words:
            test_line = f"{current_line} {word}".strip()
            test_surface = font.render(test_line, True, color)
            if max_width is not None and test_surface.get_width() > max_width:
                lines.append(current_line)
                current_line = word
            else:
                current_line = test_line
        lines.append(current_line)

        y_offset = 10
        for line in lines:
            line_surface = font.render(line, True, color)
            line_rect = line_surface.get_rect(center=(position[0], position[1] + y_offset))
            self.screen.blit(line_surface, line_rect)
            y_offset += font.get_linesize()

    def draw(self):
        """
        Render the question screen, including the question, options, and feedback.
        """
        self.screen.fill(WHITE)
        self.screen.blit(BG, (0, 0))
        max_question_width = self.screen.get_width() - 200
        self.draw_text(self.question_text, (self.screen.get_width() / 2, 100), FONT4, BLACK, max_question_width)

        score_surface = FONT.render(f"Score: {self.score.getScore()}", True, BLACK)
        score_rect = score_surface.get_rect(center=(self.screen.get_width() / 2, 50))
        self.screen.blit(score_surface, score_rect)

        feedback_surface = FONT.render(self.feedback_text, True, BLACK)
        feedback_rect = feedback_surface.get_rect(center=(self.screen.get_width() / 2, 500))
        self.screen.blit(feedback_surface, feedback_rect)

        mouse_pos = pygame.mouse.get_pos()
        self.back_button2.changeColor(mouse_pos)
        self.back_button2.update(self.screen)

        for button in self.buttons:
            button.changeColor(mouse_pos)
            button.update(self.screen)

        pygame.display.flip()


# The QuestionScreen class can be used in the main game file to render a question screen
# when a button on the game board is pressed.

