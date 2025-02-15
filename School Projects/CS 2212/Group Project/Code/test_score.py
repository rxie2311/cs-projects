import unittest
from Score import *

class TestScore(unittest.TestCase):
    def setUp(self):
        with open("score.txt", "w") as file:
            file.write("1000\n")
            file.write("5, 4, 3, 2, 1")
        self.score = Score()

    def test_loadScore_loadQuestionInfo(self):
        #checks the load methods are returning the correct output
        self.assertEqual(1000, self.score.score)
        self.assertEqual([5, 4, 3, 2, 1], self.score.questionInfo)

    def test_loadEmpty(self):
        #erasese the text file
        with open("score.txt", "w") as file:
            pass
        blankScore = Score()
        #checks that a blank file creates a Score object with 0
        self.assertEqual(0, blankScore.score)
        self.assertEqual([0, 0, 0, 0, 0], blankScore.questionInfo)

    def test_getScore(self):
        #checks getScore returns correct score
        self.assertEqual(1000, self.score.getScore())

    def test_updateScore(self):
        #adds 200 to current score
        self.score.updateScore(200)
        #checks current score has been updated
        self.assertEqual(1200, self.score.score)

    def test_updateNegScore(self):
        #subtracts 200 from current score
        self.score.updateNegScore(200)
        #checks current score has been updated
        self.assertEqual(800, self.score.score)

    def test_increaseQuestionCount(self):
        #increases 3 subjects question count by 1
        self.score.increase_questionCount("math")
        self.score.increase_questionCount("science")
        self.score.increase_questionCount("english")
        #checks that each subject specified increased by 1
        self.assertEqual([6, 5, 3, 2, 2], self.score.questionInfo)

    def test_getQuestionInfo(self):
        #checks if question count for math is correct through get method
        self.assertEqual(5, self.score.get_questionInfo("math"))

    def test_saveScore(self):
        self.score.updateScore(1000)
        self.score.increase_questionCount("math")
        self.score.increase_questionCount("science")
        self.score.increase_questionCount("english")
        self.score.save_score()
        self.assertEqual(2000, self.score.load_score())
        self.assertEqual([6, 5, 3, 2, 2], self.score.load_questionInfo())

    def tearDown(self):
        with open("score.txt", "w") as file:
            pass

if __name__ == '__main__':
    unittest.main()