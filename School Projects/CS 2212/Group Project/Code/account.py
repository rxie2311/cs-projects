from player import Player
import re

def createAccount(datafile, username, password):
    """
    Helper method that creates a Player object for new users and writes into a data file.

    :param datafile: The txt file account information is stored in
    :param username: String; User choice for a username to be saved.
    :param password: String; User choice for a password to be saved.

    :return: Returns True if successful, False otherwise.
    """

    # Opens the file with player data inside
    playerInfo = open(datafile, "r+")
    # Read data from file
    content = playerInfo.read()

    # If the specified username is in the file
    if username in content:
        # Prints out username taken and returns False
        print("Username taken.")
        playerInfo.close()
        return False
    else:
        # If the specified username is not in the file, creates a new account and returns True
        playerInfo.write("{}, {}".format(username, password))
        playerInfo.write("\n0, 0, 0")
        playerInfo.write("\n0, 0, 0, 0, 0")
        playerInfo.write("\n0")
        playerInfo.write("\n0\n")
        playerInfo.close()
        #print("Account created!\nWelcome {}".format(username))
        playerInfo.close()
        return True

def login(datafile, username, password):
    """
    Helper method that upon login, constructs a new 'Player' object by searching for a username and password in the
    data file.

    :param datafile: The txt file account information is stored in
    :param username: String; The username that is inputted on interface
    :param password: String; The password that is inputted on interface

    :return: Returns True if successful, False otherwise.
    """

    # Opens the file with player data inside
    with open(datafile, "r") as f:
        info = f.readlines()
        # Finds the using logging in and saves their info
        line1, line2, line3, line4, line5 = "", "", "", "", ""
        for i in range(0, len(info), 5):
            if info[i].strip().split(", ")[0] == username and info[i].strip().split(", ")[1] == password:
                line1 = info[i]
                line2 = info[i+1]
                line3 = info[i+2]
                line4 = info[i+3]
                line5 = info[i+4]
                break
        # If the line is empty
        if line1 == "":
            print("Wrong username or password.")
            return False

    # Moves current player to top of file
    with open(datafile, "w") as f:
        f.write(line1)
        f.write(line2)
        f.write(line3)
        f.write(line4)
        f.write(line5)
        for i in range(0, len(info), 5):
            if info[i].split(", ")[0] != username:
                f.write(info[i])
                f.write(info[i + 1])
                f.write(info[i + 2])
                f.write(info[i + 3])
                f.write(info[i + 4])
        return True

def deleteAccount(datafile, username):
    """
    Helper method that deletes a player from the player info file.

    :param datafile: The txt file account information is stored in
    :param username: String; The player that will be deleted.

    :return: Returns True if successful, False otherwise.
    """

    # Opens the file with player data inside
    with open(datafile, "r") as f:
        info = f.readlines()
    with open(datafile, "w") as f:
        found = False
        for i in range(0, len(info), 5):
            # If the username specified is found, returns true
            if info[i].split(", ")[0] == username:
                found = True
            else:
                f.write(info[i])
                f.write(info[i + 1])
                f.write(info[i + 2])
                f.write(info[i + 3])
                f.write(info[i + 4])

    # If found is true, then return true to delete
    if found:
        print("Delete successful.")
        return True
    # If found is not true, then return false
    else:
        print("User does not exist.")
        return False
