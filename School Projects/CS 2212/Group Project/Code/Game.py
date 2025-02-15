from question import Question
from player import *
from achievements import *
from question import ConcreteQuestionClass
from Score import Score

class Game:
    """
    The Game class handles all the backend variables needed for the game to run.
    """

    def __init__(self, player, level):
        """
        Constructor method that initializes a new game.

        :param player: Player; Player profile that is playing the game.
        :param level: int; Level that the game is currently on.

        :return: void method; Does not return anything.
        """

        # Player
        self.player = player
        # Level - Start with level 1
        self.level = 1

        # Question related variables
        self.questionsCorrect = 0
        self.mathQCorrect = 0
        self.engQCorrect = 0
        self.sciQCorrect = 0
        self.geoQCorrect = 0
        self.hisQCorrect = 0

        # Board
        self.board = None
        # Method to fill board with questions
        self.fillBoard(level)

        # Subject Order per level
        self.subjects_order = {
            1: ["Math", "Science", "English"],
            2: ["Math", "Science", "English", "Geography"],
            3: ["Math", "Science", "English", "Geography", "History"]
        }
        # Board points per row
        self.points_per_row = [200, 400, 600]
        # Question generator method
        self.questionGenerator = ConcreteQuestionClass('questions.csv')

    def fillBoard(self, new_level):
        """
        Helper method that fills the board with questions based on the current level of the game.

        :param new_level: int; The level that the game is currently on.

        :return: void method; Does not return anything.
        """

        self.level = new_level
        if self.board is not None:
            existing_rows, existing_columns = len(self.board), len(self.board[0])
        else:
            existing_rows, existing_columns = 0, 0

    # Number of columns determined by the length of subject_order levels (1,2,3)
        new_columns = len(self.subjects_order[self.level])
        new_board = [[None for _ in range(new_columns)] for _ in range(3)]  # Always 3 rows

        for i in range(existing_rows):
            for j in range(existing_columns):
                new_board[i][j] = self.board[i][j]

    # Iterates through points_per_row index to generate subject questions in every column
        for i in range(3):
            for j in range(existing_columns, new_columns):
                subject = self.subjects_order[self.level][j]
                points = self.points_per_row[i]
                # Generate question using ConcreteQuestionClass
                question = self.questionGenerator.generateQuestion(subject, points)
                if question:
                    new_board[i][j] = question
                else:
                    print(f"No question available for {subject} with {points} points.")

        self.board = new_board

    def selectQuestion(self, row, column):
        """
        Helper method that selects question data from a selected cell in the grid for front-end to display,
        compare answer and update points.

        :param row: int; The row index of the question to be selected.
        :param column: int; The column index of the question to be selected.

        :return: void method; Does not return anything.
        """

        selectedQuestion = self.board[row][column]
        questionStr = selectedQuestion.questionStr
        answerStr = selectedQuestion.answerStr
        points = selectedQuestion.questionPoints
        # 'userAnswer' is sample answer (to be integrated with GUI)
        userAnswer = input("Your answer: ")

        # Check if the answer is correct
        correct = selectedQuestion.isCorrect(userAnswer)
        subject = selectedQuestion.subject

        if correct:
            self.updateScore(selectedQuestion.questionPoints)
            self.questionsCorrect += 1  # Increment the correct questions counter
            if subject == 'math':
                self.mathQCorrect += 1
            elif subject == 'english':
                self.engQCorrect += 1
            elif subject == 'science':
                self.sciQCorrect += 1
            elif subject == 'geography':
                self.geoQCorrect += 1
            elif subject == 'history':
                self.hisQCorrect += 1

    def levelDone(self, questionsCorrect):
        """
        Helper method that checks if the current level is done by checking how many questions the player has answered
        correctly.

        :param questionsCorrect: int; The number of correctly answered questions.

        :return: True if the question requirement is met and the user can progress to the next level, False otherwise.
        """

        if self.board.getLevel() == 1:
            if questionsCorrect == 2:
                return True
            else:
                return False

        elif self.board.getLevel() == 2:
            if questionsCorrect == 2:
                return True
            else:
                return False

        elif self.board.getLevel() == 3:
            if questionsCorrect == 2:
                return True
            else:
                return False

    def getQuestionsCorrect(self):
        """
        Helper method that returns the total number of questions answered correctly by the player.

        :return: questionsCorrect (int): The number of correctly answered questions in this level.
        """

        return self.questionsCorrect

    def setQuestionsCorrect(self, correct):
        """
        Helper method that sets the total number of questions answered correctly by the player.

        :param correct: int; The number that is to be set as the questions answered correctly.

        :return: void method; Does not return anything.
        """

        self.questionsCorrect = correct
