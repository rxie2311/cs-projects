class Player:
    """
    The Player class represents a user that can log in and save progress.
    """

    def __init__(self, username: str, password: str, gameInfo, questionInfo, achievements, avatarID: int):
        """
        Constructor that generates a Player object, which stores all of a Player's stats and info.

        :param username: String; The player's username.
        :param password: String; The player's password.
        :param gameInfo: An array that stores player stats.
        :param questionInfo: An array that stores the number of questions the player has answered correctly for each subject.
        :param achievements: An array that stores the player's unlocked achievements.

        :return: void method; Does not return anything.
        """

        self.username = username
        self.password = password
        self.gameInfo = gameInfo
        self.questionInfo = questionInfo
        self.achievements = achievements
        self.avatarID = avatarID

    def getUsername(self):
        """
        Helper method that returns player's username.

        :return: Player's username.
        """

        return self.username

    def getPassword(self):
        """
        Helper method that returns player's password.

        :return: Player's password.
        """

        return self.password

    def getHighScore(self):
        """
        Helper method that returns player's highscore on the profile.

        :return: Player's highscore record on the profile.
        """

        return self.gameInfo[0]

    def setHighScore(self, newScore):
        """
        Helper method that sets a player's highscore on the profile.

        :param newScore: int; Highscore to be set as the player's highscore.

        :return: void method; Does not return anything.
        """

        self.gameInfo[0] = newScore

    def getNumGames(self):
        """
        Helper method that returns the total number of games the player has played.

        :return: Player's number of games played stat.
        """

        return self.gameInfo[1]

    def increaseNumGames(self):
        """
        Helper method that increases the total number of games played by 1.

        :return: void method; Does not return anything.
        """

        numGames = int(self.gameInfo[1])
        numGames += 1
        self.gameInfo[1] = str(numGames)

    def getGamesWon(self):
        """
        Helper method that returns the total number of games the player has won.

        :return: Player's number of games won stat.
        """

        return self.gameInfo[2]

    def increaseGamesWon(self):
        """
        Helper method that increases the total number of games won by 1.

        :return: void method; Does not return anything.
        """

        numGames = int(self.gameInfo[2])
        numGames += 1
        self.gameInfo[2] = str(numGames)

    def getNumQuestions(self, subject):
        """
        Helper method that returns the total number of questions a user has answered correctly for a specific subject.

        :param subject: String; The subject that is to be searched for.

        :return: Player's total number of questions answered correctly for the subject, or False if invalid subject.
        """

        if subject == "math":
            x = 0
        elif subject == "science":
            x = 1
        elif subject == "geography":
            x = 2
        elif subject == "history":
            x = 3
        elif subject == "english":
            x = 4
        else:
            print("Not a subject")
            return False
        return self.questionInfo[x]

    def increaseQuestion(self, amount, subject):
        """
        Helper method that increases the total number of questions a user has answered correctly for a specific subject
        by an amount.

        :param subject: String; The subject that is to be searched for.
        :param amount: int; The amount that the total is to be increased by.

        :return: False if invalid subject.
        """

        if subject == "math":
            x = 0
        elif subject == "science":
            x = 1
        elif subject == "geography":
            x = 2
        elif subject == "history":
            x = 3
        elif subject == "english":
            x = 4
        else:
            print("Not a subject")
            return False
        numQuestions = int(self.questionInfo[x])
        numQuestions += amount
        self.questionInfo[x] = str(numQuestions)

    def getAchievements(self):
        """
        Helper method that returns an array with the player's achievements.

        :return: Player's unlocked achievements in an array.
        """

        return self.achievements

    def addAchievement(self, achievement):
        """
        Helper method that adds an achievement to player's achievement array.

        :param achievement: int; The achievement number that is to be added.

        :return: void method; Does not return anything.
        """

        self.achievements.append(achievement)

    def removeAchievement(self, achievement):
        """
        Helper method that removes an achievement from the player's achievement array.

        :param achievement: int; The achievement number that is to be removed.

        :return: void method; Does not return anything.
        """

        for i in range(0, len(self.achievements)):
            if achievement == self.achievements[i]:
                self.achievements.pop(i)

    def getAvatarID(self):
        return self.avatarID

    def setAvatarID(self, num):
        self.avatarID = num
def currentUser(datafile):
    """
    Helper method that retrieves the current user and creates a 'Player' object for them.

    :param datafile: The txt file account information is stored in
    :return: New Player object with user inputted info stored in it.
    """

    try:
        playerInfo = open(datafile, "r")
    except Exception:
        return False
    lines = playerInfo.readlines()
    #reads the first player in the file and creates an Player object
    username, password = lines[0].strip().split(", ")
    game = [int(x) for x in lines[1].strip().split(", ")]
    questions = [int(x) for x in lines[2].strip().split(", ")]
    achievements = [int(x) for x in lines[3].strip().split(", ")]
    avatarID = int(lines[4].strip())
    playerInfo.close()
    return Player(username, password, game, questions, achievements, avatarID)

def saveUser(player: Player):
    """
    Helper method that saves the player's game progress into a player profile after the game ends.

    :param player: The player profile that the game progress will be saved to.

    :return: void method; Does not return anything.
    """

    p = player
    with open("accounts.txt", "r") as f:
        info = f.readlines()
    with open("accounts.txt", "w") as f:
        user = p.getUsername()
        #writes player's information at top of file
        f.write("{}, {}\n".format(user, p.getPassword()))
        f.write("{}, {}, {}\n".format(p.getHighScore(), p.getNumGames(), p.getGamesWon()))
        f.write("{}, {}, {}, {}, {}\n".format(p.getNumQuestions("math"), p.getNumQuestions("science"),
                                              p.getNumQuestions("geography"), p.getNumQuestions("history"),
                                              p.getNumQuestions("english")))
        for i in range(len(p.getAchievements())):
            if i == len(p.getAchievements()) - 1:
                f.write("{}\n".format(p.getAchievements()[i]))
            else:
                f.write("{}, ".format(p.getAchievements()[i]))
        f.write(str(p.getAvatarID()) + "\n")
        #writes rest of players after that
        for i in range(0, len(info), 5):
            if info[i].split(", ")[0] != user:
                f.write(info[i])
                f.write(info[i + 1])
                f.write(info[i + 2])
                f.write(info[i + 3])
                f.write(info[i + 4])
    print("Save successful")
