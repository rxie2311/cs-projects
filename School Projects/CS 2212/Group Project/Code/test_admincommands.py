import unittest
from admincommands import *

class TestAdminCommands(unittest.TestCase):
    def setUp(self):
        with open("accounts.txt", "a") as f:
            f.write("unittest1, testpass\n1000, 1, 1\n0, 0, 0, 0, 0\n 0, 1\n")
            f.write("unittest2, testpass\n100, 0, 0\n0, 0, 0, 0, 0\n0, 1, 2\n")
    def test_displayPlayer(self):
        list = displayUsernames()
        if "unittest1" in list and "unittest2" in list:
            correct = True
        else:
            correct = False
        self.assertTrue(correct)

    def test_displayStats(self):
        stats = displayStats("unittest1").strip().split("\n")
        if stats[0] == "User: unittest1" and stats[1] == "Highscore: 1000" and stats[2] == "Games Played: 1" and stats[3] == "Games Won: 1":
            correct = True
        else:
            correct = False
        self.assertTrue(correct)

    def tearDown(self):
        with open("accounts.txt", "r") as f:
            content = f.readlines()
        with open("accounts.txt", "w") as f:
            for i in range(0, len(content) - 8):
                f.write(content[i])

if __name__ == '__main__':
    unittest.main()
