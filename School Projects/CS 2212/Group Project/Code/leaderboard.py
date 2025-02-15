from player import *

def listPlayers(datafile):
    """
    Helper method that creates a list of players and returns it.

    :param datafile: The txt file account information is stored in
    :return: The list of players created by the method.
    """

    try:
        playerInfo = open(datafile, "r")
    except Exception:
        return False
    playerList = []
    lines = playerInfo.readlines()
    for i in range(0, len(lines), 5):
        user, pw = lines[i].strip().split(", ")
        game = [int(x) for x in lines[i + 1].strip().split(", ")]
        questions = [int(x) for x in lines[i + 2].strip().split(", ")]
        achievements = [int(x) for x in lines[i + 3].strip().split(", ")]
        avatarID = lines[i+4]
        if user == "admin":
            pass
        else:
            playerList.append(Player(user, pw, game, questions, achievements, avatarID))
    playerInfo.close()
    return playerList

def sortHighScore(playerList: list[Player]):
    """
    Helper method that sorts an array of 'Player' objects by player highscore from greatest to least.

    :param playerList: A list of players.

    :return: The result of a function call to sorted, a sorted by highscore player list.
    """

    return sorted(playerList, key=lambda x: x.gameInfo[0], reverse=True)

def sortAchievements(playerList: list[Player]):
    """
    Helper method that returns array of 'Player' objects sorted by total number of achievements from greatest to least.

    :param playerList: A list of players.

    :return: The result of a function call to sorted, a sorted by achievements player list.
    """

    return sorted(playerList, key=lambda x: len(x.achievements), reverse=True)
