
def jumpToLevel():
    """
    Helper method to allow admin level players to jump to a level of their choice.

    :param level: int; Level number that the player wants to jump to.

    :return: Update when changed.
    """

    pass

def displayUsernames():
    """
    Helper method that displays a list of usernames from all local players.

    :return: playerList holding all local player usernames.
    """

    try:
        playerInfo = open("accounts.txt", "r")
    except Exception:
        return False
    playerList = []
    lines = playerInfo.readlines()
    for i in range(0, len(lines), 5):
        user = lines[i].split(", ")[0]
        if user == "admin":
            pass
        else:
            playerList.append(user)
    playerInfo.close()
    return playerList

def displayStats(username):
    """
    Helper method that displays all the player's stats.

    :param username: String; The player that will have their stats displayed.

    :return: False, if the username is invalid.
    """

    with open("accounts.txt", "r") as f:
        info = f.readlines()
        line1, line2, line3, line4 = "", "", "", ""
        for i in range(0, len(info), 4):
            if info[i].split(", ")[0] == username:
                line1 = info[i]
                line2 = info[i+1].strip().split(", ")
                line3 = info[i+2].strip().split(", ")
                line4 = info[i+3].strip()
                break
        if line1 == "":
            print("Username does not exist")
            return False
    string = ""
    string += ("User: {}\n".format(username))
    string += ("Highscore: {}\nGames Played: {}\nGames Won: {}\n".format(line2[0], line2[1], line2[2]))
    string += ("Number of Correct Answers\nMath: {}, Science: {}, Geography: {}, History: {}, English: {}\n".format(line3[0], line3[1], line3[2], line3[3], line3[4]))
    if line4 == "0":
        line4 = "None"
    else:
        line4 = line4.lstrip("0, ")
    string += ("Achievements Unlocked: " + line4)
    return string