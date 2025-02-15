from player import Player

# Numerical Achievement Guide:
# Each number corresponds to an achievement. The numbers are used to refer to these achievements in the code.
# 1. Complete 10 games.
# 2. Win 10 games.
# 3. Get a high score of 5000 points.
# 4. Answer 20 Math questions correctly.
# 5. Answer 20 Science questions correctly.
# 6. Answer 20 Geography questions correctly.
# 7. Answer 20 History questions correctly.
# 8. Answer 20 English questions correctly.
# 9. Complete all achievements.


def isDone(player, num):
    """
    Helper method that checks if the player has unlocked an achievement.

    :param num: int; The achievement number that will be checked.

    :return: (Boolean): True if the player has unlocked it.
    """

    # Checks if the player completed the achievement, if completed, return True
    if num in player.getAchievements():
        return True
    # If not completed, return False
    else:
        return False


def checkQuestionAchievement(player, num, subject):
    """
    Helper method that checks the progress on achievements 4-8 by checking the player profile for number of questions
    answered for each subject (Math, Science, Geography, History and English).
    
    :param player: Player; Player object that needs to be updated with the achievements.
    :param num: int; The achievement number that will be granted if the player has enough questions answered.
    :param subject: String; Used to check for the subject that is listed in the achievement.

    :return: void method; Does not return anything.
    """

    # Checks if the player has completed the achievements that require answering different question types correctly
    if not isDone(player, num):
        # If requirement is met, add the achievement to player's profile
        if int(player.getNumQuestions(subject)) >= 20:
            player.addAchievement(num)


def checkAchievements(player):
    """
    Helper method that checks player's stats and compares with unlock conditions of the achievement.
    If the player has successfully fulfilled the requirements, then the method will grant the player the
    achievement.
    
    :param player: Player; Player object that needs to be updated with the achievements.

    :return: void method; Does not return anything.
    """

    # Checks if the achievement conditions are reached for achievements 1, 2 and 3
    if not isDone(player, 1):
        if int(player.getNumGames()) >= 10:
            player.addAchievement(1)
    if not isDone(player, 2):
        if int(player.getGamesWon()) >= 10:
            player.addAchievement(2)
    if not isDone(player, 3):
        if int(player.getHighScore()) >= 5000:
            player.addAchievement(3)

    # Calls on a function to check for achievements 4, 5, 6, 7 and 8
    checkQuestionAchievement(player, 4, "math")
    checkQuestionAchievement(player, 5, "science")
    checkQuestionAchievement(player, 6, "geography")
    checkQuestionAchievement(player, 7, "history")
    checkQuestionAchievement(player, 8, "english")

    # If all achievements are unlocked, adds achievement 9 to player profile
    if not isDone(player, 9):
        if len(player.getAchievements()) == 9:
            player.addAchievement(9)


def displayProgress(player, achievementNum):
    """
    Helper method that displays the progress that the player has on a specified achievement number (1-9).
    
    :param player: Player; Player object that needs to be updated with the achievements.
    :param achievementNum: int; The achievement number that will be used to select an achievement to view current progress.

    :return: void method; Does not return anything.
    """

    # Displays the progress the player has on each achievement
    if achievementNum == 1:
       return("{}/10".format(player.getNumGames()))
    elif achievementNum == 2:
        return("{}/10".format(player.getGamesWon()))
    elif achievementNum == 3:
        return("{}/5,000".format(player.getHighScore()))
    elif achievementNum == 4:
        return("{}/20".format(player.getNumQuestions("math")))
    elif achievementNum == 5:
        return("{}/20".format(player.getNumQuestions("science")))
    elif achievementNum == 6:
        return("{}/20".format(player.getNumQuestions("geography")))
    elif achievementNum == 7:
        return("{}/20".format(player.getNumQuestions("history")))
    elif achievementNum == 8:
        return("{}/20".format(player.getNumQuestions("english")))
    elif achievementNum == 9:
        done = len(player.getAchievements()) - 1
        return("{}/8".format(done))
