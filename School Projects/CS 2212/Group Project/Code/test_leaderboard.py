import unittest
from leaderboard import *

class TestLeaderboard(unittest.TestCase):
    def setUp(self):
        with open("unittest.txt", "w") as f:
            f.write("unittest1, testpass\n1000, 0, 0\n0, 0, 0, 0, 0\n 0, 1\n")
            f.write("unittest2, testpass\n100, 0, 0\n0, 0, 0, 0, 0\n0, 1, 2\n")

    def test_listPlayers(self):
        list = listPlayers("unittest.txt")
        player1 = list[-2]
        player2 = list[-1]
        if player1.getUsername() == "unittest1" and player2.getUsername() == "unittest2":
            correct = True
        else:
            correct = False
        self.assertTrue(correct)

    def test_sortHighScore(self):
        list = listPlayers("unittest.txt")
        highscorelist = sortHighScore(list)
        for i in range(0, len(highscorelist)):
            if highscorelist[i].getUsername() == "unittest1":
                pos1 = i
            elif highscorelist[i].getUsername() == "unittest2":
                pos2 = i
        self.assertLess(pos1, pos2)

    def test_sortAchievements(self):
        list = listPlayers("unittest.txt")
        achievementslist = sortAchievements(list)
        for i in range(0, len(achievementslist)):
            if achievementslist[i].getUsername() == "unittest1":
                pos1 = i
            elif achievementslist[i].getUsername() == "unittest2":
                pos2 = i
        self.assertGreater(pos1, pos2)

    def tearDown(self):
        with open("unittest.txt", "w") as f:
            pass
        

if __name__ == '__main__':
    unittest.main()
