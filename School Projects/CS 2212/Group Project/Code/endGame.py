from player import *
from achievements import *
from Score import *

def endGame(score: Score):
    """
    Helper method that saves the user's stats and high score at the end of the game.

    :param player: The player profile that the stats will be saved into.
    :param score: The score that will be saved into the player profile.

    :return: void method; Does not return anything.
    """

    player = currentUser("accounts.txt")
    if score.getScore() > player.getHighScore(): #score = final score
        player.setHighScore(score.getScore())
    player.increaseNumGames()
    #if won: #won is boolean for if game is completed
        #player.increaseGamesWon()
    player.increaseQuestion(score.get_questionInfo("math"), "math") #numMath = tally of math questions answered right
    player.increaseQuestion(score.get_questionInfo("science"), "science")
    player.increaseQuestion(score.get_questionInfo("geography"), "geography")
    player.increaseQuestion(score.get_questionInfo("history"), "history")
    player.increaseQuestion(score.get_questionInfo("english"), "english")
    checkAchievements(player) #checks if player has unlocked any new achievements
    saveUser(player)
    score.resetScore()
