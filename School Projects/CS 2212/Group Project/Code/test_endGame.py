import unittest
from endGame import *
from player import Player
from account import deleteAccount

class TestEndGame(unittest.TestCase):
    def test_saveUser(self):
        player = Player("unittest", "testpass", ["100", "5", "10"], ["1", "2", "3", "4", "5"], [0, 1, 8])
        saveUser(player)
        file = open("accounts.txt", "r")
        lines = file.readlines()
        if lines[0] == "unittest, testpass\n" and lines[1] == "100, 5, 10\n" and lines[2] == "1, 2, 3, 4, 5\n" and lines[3] == "0, 1, 8\n":
            correct = True
        else:
            correct = False
        file.close()
        deleteAccount("accounts.txt", "unittest")
        self.assertTrue(correct)

    #def test_endGame(self):

if __name__ == '__main__':
    unittest.main()
