import csv
import pandas as pd
import random
from player import Player, currentUser


class Question:
    """
    The Question class is used to represent a Question, used to manage questions on the board.
    """

    def __init__(self, questionID: int, subject: str, questionStr: str,
                 answerStr: str, tutorial: str, answeredCorrectly: bool,
                 questionPoints: int):
        """
        Constructor that initializes a new Question object. This object represents the questions that will be stored in
        the board.

        :param questionID: int; Each question has a unique ID that represents it.
        :param subject: String; The subject that the question is a part of.
        :param questionStr: String; The question text itself.
        :param answerStr: String; The answer to the question.
        :param typeStr: String; The type of question it is (multiple choice, fill in the blank)
        :param tutorial: String; A tutorial on how to solve the question that plays if the question is answered wrong.
        :param answeredCorrectly: boolean; Checks if the question was answered correctly or not.
        :param questionPoints: int; The point amount the question is worth.

        :return: void method; Does not return anything.
        """

        self.questionID = questionID
        self.subject = subject
        self.questionStr = questionStr
        self.answerStr = answerStr
        self.tutorial = tutorial
        self.answeredCorrectly = answeredCorrectly
        self.questionPoints = questionPoints

    def displayQuestion(self):
        """
        Helper method that displays the question and answer.

        :return: The displayed question and answer.
        """

        print(f"Question: {self.questionStr}, Answer: {self.answerStr}")
        return f"Question: {self.questionStr}, Answer: {self.answerStr}"

    def isCorrect(self, answerText: str) -> bool:
        """
        Helper method that determines if the user's provided answer matches the question's correct answer.

        :param answerText: String; The user provided answer.

        :return: (Boolean): The result of if the user provided answer matches with the question answer.
        """

        return answerText.lower() == self.answerStr.lower()

    def getAnswer(self) -> str:
        """
        Helper method that returns the question's answer.

        :return: answerStr (String): The correct answer to the question.
        """

        return self.answerStr


class QuestionFactory:
    """
    The QuestionFactory class is used to pull Questions from a file.
    """

    # Initialize question counter
    counter = 1

    def __init__(self, questionFile):
        """
        Constructor that takes a file to read and store the questions within into a 2D array.

        :param questionFile: The file name that stores all the questions to be used in the game.

        :return: void method; Does not return anything.
        """

        self.questions = self.loadQuestions(questionFile)
        self.usedQuestions = set()

    def loadQuestions(self, questionFile) -> dict:
        """
        Helper method that loads questions from the file into a dictionary to be moved into the board.

        :param questionFile: The file name that stores all the questions to be used in the game.

        :return: questionsDict (Dictionary): Used to store questions, answers, subjects, types and points.
        """

        # Load questions from a CSV file into a dictionary
        questionsDict = {}
        df = pd.read_csv(questionFile)
        for index, row in df.iterrows():
            # Parse each row and create Question objects
            subject = row['subject']
            questionPoints = int(row['questionPoints'])
            questionStr = row['question']
            answerStr = row['answer']
            #typeStr = row['type']
            tutorial = row['tutorial']
            questionID = QuestionFactory.counter
            QuestionFactory.counter += 1

            question = Question(questionID, subject, questionStr, answerStr, tutorial, False, questionPoints)

            if subject not in questionsDict:
                questionsDict[subject] = {}
            if questionPoints not in questionsDict[subject]:
                questionsDict[subject][questionPoints] = []

            questionsDict[subject][questionPoints].append(question)

        return questionsDict

    def generateQuestion(self, subject: str, questionPoints: int) -> Question:
        """
        Helper method that generates a question based on the point value and the subject.

        :param subject: String; Specifies the question subject needed.
        :param questionPoints: int; Specifies the question points needed.

        :return: Question object if successful, False otherwise.
        """

        # Generate a random question based on subject and point value
        if subject in self.questions and questionPoints in self.questions[subject]:
            questionList = self.questions[subject][questionPoints]
            unusedQuestions = [q for q in questionList if q.questionID not in self.usedQuestions]
            if unusedQuestions:
                selectedQuestion = random.choice(unusedQuestions)
                self.usedQuestions.add(selectedQuestion.questionID)
                return selectedQuestion
            else:
                print(f"No unused questions available for {subject} level {questionPoints}")
        else:
            print(f"No questions available for {subject} level {questionPoints}")

    def addQuestion(self, subject: str, questionPoints: int, questionStr: str,
                    answerStr: str, tutorial: str, questionFile):
        """
        Helper method that adds a question into the file.

        :param questionFile: File for the question to be written into.
        :param subject: String; The subject that the question is a part of.
        :param questionPoints: int; The point amount the question is worth.
        :param questionStr: String; The question text itself.
        :param answerStr: String; The answer to the question.
        :param tutorial: String; A tutorial on how to solve the question that plays if the question is answered wrong.

        :return: void method; Does not return anything.
        """

        # Add a new question to the CSV file
        if self.checkAdminStatus():  # Check admin status
            QuestionFactory.counter += 1

            newQuestion = {
                'subject': subject,
                'questionPoints': questionPoints,
                'question': questionStr,
                'answer': answerStr,
                'tutorial': tutorial
            }

            # Append the new question to the CSV file
            with open(questionFile, mode='a', newline='\n') as csvfile:
                fieldnames = ['subject', 'questionPoints', 'question', 'answer', 'tutorial'] # MUST ENTER SUBJECT NAMES IN LOWERCASE
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            # Convert the new question into a DataFrame
            new_question_df = pd.DataFrame([newQuestion])

            writer.writerow(newQuestion)
            # Append the new question DataFrame to the CSV file
            with open(questionFile, mode='a', newline='\n') as csvfile:
                new_question_df.to_csv(csvfile, header=False, index=False)
                csvfile.write('\n')
            print("Question added successfully.")

    def checkAdminStatus(self):
        """
        Helper method that checks if the user is an Admin or not.

        :return: (Boolean): The result represents if the user has Admin role.
        """

        currentPlayer = currentUser("accounts.txt")
        return currentPlayer.getUsername() == "admin"


class ConcreteQuestionClass:
    """
    The ConcreteQuestionClass is used for generating questions.
    """

    def __init__(self, questionFile):
        """
        Constructor that takes a file to read and generate a question that fits the requirements.

        :param questionFile: The file name that stores all the questions to be used in the game.

        :return: void method; Does not return anything.
        """

        self.questionFactory = QuestionFactory(questionFile)

    def generateQuestion(self, subject: str, level: int) -> Question:
        """
        Helper method that generates a question based on the subject it is and points it is worth.

        :param subject: String; The subject that the question is a part of.
        :param level: int; The point amount the question is worth.

        :return: (Question): The question object generated from the requirements
        """

        # Generate a question using the QuestionFactory
        return self.questionFactory.generateQuestion(subject, level)


# Test the code
'''
questionFile = 'question.csv'
concreteQuestion = ConcreteQuestionClass(questionFile)
randomQuestion = concreteQuestion.generateQuestion('math', 200)
questionFactory = QuestionFactory(questionFile)

if randomQuestion:
    print(f"Question ID: {randomQuestion.questionID}")
    print(f"Question: {randomQuestion.questionStr}")
    print(f"Answer: {randomQuestion.answerStr}")
    print(f"Tutorial: {randomQuestion.tutorial}")
    print(f"Subject: {randomQuestion.subject}")


questionFactory.addQuestion('science', 200, 'What is the capital of France?','Paris', 'Find a map')
questionFactory.addQuestion('science', 200, 'What is the capital of France?','Paris', 'Find a map')
'''

