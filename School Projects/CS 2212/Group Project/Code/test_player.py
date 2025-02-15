import unittest
from player import *
from account import *

class TestPlayer(unittest.TestCase):
    def setUp(self):
        self.player = Player("unittest", "testpass", [0, 0, 0], [0, 0, 0, 0, 0], [0], 0)

    def test_getUsername(self):
        self.assertEqual(self.player.getUsername(), "unittest")

    def test_getPassword(self):
        self.assertEqual(self.player.getPassword(), "testpass")

    def test_get_set_HighScore(self):
        self.player.setHighScore("1000")
        self.assertEqual(self.player.getHighScore(), "1000")

    def test_get_set_GamesPlayed(self):
        for i in range(0, 10):
            self.player.increaseNumGames()
        self.assertEqual(self.player.getNumGames(), "10")

    def test_get_set_GamesWon(self):
        for i in range(0, 5):
            self.player.increaseGamesWon()
        self.assertEqual(self.player.getGamesWon(), "5")

    def test_get_set_Questions(self):
        self.player.increaseQuestion("math", 1)
        self.player.increaseQuestion("science", 2)
        self.player.increaseQuestion("geography", 3)
        self.player.increaseQuestion("history", 4)
        self.player.increaseQuestion("english", 5)
        if (self.player.getNumQuestions("math") == "1" and
            self.player.getNumQuestions("science") == "2" and
            self.player.getNumQuestions("geography") == "3" and
            self.player.getNumQuestions("history") == "4" and
            self.player.getNumQuestions("english") == "5"):
            correct = True
        else:
            correct = False

        self.assertTrue(correct)

    def test_add_get_Achievements(self):
        self.player.addAchievement(1)
        self.player.addAchievement(9)
        self.assertEqual(self.player.getAchievements(), [0, 1, 9])

    def test_set_get_AvatarID(self):
        self.player.setAvatarID(1)
        self.assertEqual(1, self.player.getAvatarID())

    def test_currentUser(self):
        with open("unittest.txt", "w") as f:
            f.write("unittest1, testpass\n1000, 0, 0\n0, 0, 0, 0, 0\n 0, 1\n0\n")
            f.write("unittest2, testpass\n100, 0, 0\n0, 0, 0, 0, 0\n0, 1, 2\n1\n")
        user = currentUser("unittest.txt")
        self.assertEqual(user.getUsername(), "unittest1")
        with open("unittest.txt", "w") as f:
            pass
if __name__ == '__main__':
    unittest.main()
