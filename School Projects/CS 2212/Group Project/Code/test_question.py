import unittest
from question import Question
from question import QuestionFactory
from question import ConcreteQuestionClass

class TestQuestion(unittest.TestCase):

    # TESTING QUESTION CLASS:

    # Testing the displayQuestion function
    def test_displayQuestion(self):
        question = Question(1, "math", "What is 1+1 A: 1 B: 2 C: 3 D: 4", "2", "1+1=2", True, 200)
        generated_string = question.displayQuestion()
        expected_string = f"Question: {question.questionStr}, Answer: {question.answerStr}"

        self.assertEqual(generated_string, expected_string)

    # Testing the isCorrect function
    def test_isCorrect(self):
        user_answer = "3"
        question = Question(1, "math", "What is 1+2 A: 1 B: 2 C: 3 D: 4", "3", "1+2=3", True, 200)
        self.assertTrue(question.isCorrect(user_answer))

    def test_isWrong(self):
        user_answer = "0"
        question = Question(1, "math", "What is 1+2 A: 1 B: 2 C: 3 D: 4", "3", "1+2=3", True, 200)
        self.assertFalse(question.isCorrect(user_answer))

    # Testing the getAnswer function
    def test_getAnswer(self):
        question = Question(1, "math", "What is 1+1 A: 1 B: 2 C: 3 D: 4", "2", "1+1=2", True, 200)
        generated_answer = question.getAnswer()
        expected_answer = question.answerStr

        self.assertEqual(expected_answer, generated_answer)

    # TESTING CONCRETEQUESTION CLASS:

    def test_generateQuestion(self):
        #creating test file with data
        with open("unittest.csv", "w") as f:
            f.write("subject,questionPoints,question,answer,tutorial\n")
            f.write('math,600,"What is 1+1 = ? A: 1 B: 2 C: 3 D: 4",2,1+1=2\n')
            f.write('science,200,"What is the chemical symbol of Gold? A: Au B: H C: He D: Pb",Au,"The chemical symbol is Au"\n')
        # Creating new concrete question object
        questions = ConcreteQuestionClass("unittest.csv")
        # Test 1
        generated_question = questions.generateQuestion("math", 600)
        expected_question = Question(1, "math", "What is 1+1 = ? A: 1 B: 2 C: 3 D: 4", "2", '1+1=2', True, 600)

        # Test 2
        generated_question2 = questions.generateQuestion("science", 200)
        expected_question2 = Question(2, "science", "What is the chemical symbol of Gold? A: Au B: H C: He D: Pb", "Au", "The chemical symbol is Au", True, 200)

        # Test 1
        self.assertEqual(generated_question.questionID, expected_question.questionID)
        self.assertEqual(generated_question.subject, expected_question.subject)
        self.assertEqual(generated_question.questionStr, expected_question.questionStr)
        self.assertEqual(generated_question.answerStr, expected_question.answerStr)
        self.assertEqual(generated_question.questionPoints, expected_question.questionPoints)

        # Test 2
        self.assertEqual(generated_question2.questionID, expected_question2.questionID)
        self.assertEqual(generated_question2.subject, expected_question2.subject)
        self.assertEqual(generated_question2.questionStr, expected_question2.questionStr)
        self.assertEqual(generated_question2.answerStr, expected_question2.answerStr)
        self.assertEqual(generated_question2.questionPoints, expected_question2.questionPoints)

        with open("unittest.csv", "w") as f:
            pass

if __name__ == '__main__':
    unittest.main()
