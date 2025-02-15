import unittest
from account import *

class TestAccount(unittest.TestCase):
    '''
    Tests the account class which deals with creating and deleting information from a text file
    '''
    def setUp(self):
        createAccount("accounts.txt", "unittest", "testpass")

    def test_createAccount(self):
        file = open("accounts.txt", "r")
        content = file.read()
        if "unittest" in content:
            found = True
        else:
            found = False
        self.assertTrue(found)
        file.close()

    def test_createDuplicateAccount(self):
        self.assertFalse(createAccount("accounts.txt", "unittest", "testpass2"
                                                                   ""))
    def test_validLogin(self):
        login("accounts.txt", "unittest", "testpass")
        file = open("accounts.txt", "r")
        content = file.readlines()
        if content[0].split(", ")[0] == "unittest":
            found = True
        else:
            found = False
        self.assertTrue(found)
        file.close()

    def test_invalidUserLogin(self):
        self.assertFalse(login("accounts.txt", "doesnottexist", "testpass"))

    def test_invalidPassLogin(self):
        self.assertFalse(login("accounts.txt", "unittest", "wrongpass"))

    def test_deleteRealAccount(self):
        createAccount("accounts.txt", "unittest2", "testpass")
        deleteAccount("accounts.txt", "unittest2")
        file = open("accounts.txt", "r+")
        content = file.read()
        if "unittest2" in content:
            found = True
        else:
            found = False
        self.assertFalse(found)
        file.close()

    def test_deleteFakeAccount(self):
        self.assertFalse(deleteAccount("accounts.txt", "doesnotexist"))


    def tearDown(self):
        deleteAccount("accounts.txt", "unittest")

if __name__ == '__main__':
    unittest.main()
