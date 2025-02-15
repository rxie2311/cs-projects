class Score:
    """
    The Score class helps keep track of score during the game.
    """

    def __init__(self):
        """
        Constructor used to start keeping track of score in a new game.

        :return: void method; Does not return anything.
        """
        self.score = self.load_score()
        self.questionInfo = self.load_questionInfo()

    def getScore(self):
        """
        Helper method used to return the current score.

        :return: The current score.
        """
        return self.score

    def load_score(self):
        """
        Helper method used to load the current score from the file.

        :return: int; The current score loaded from the file.
        """
        try:
            with open("score.txt", "r") as file:
                content = file.readlines()
                return int(content[0].strip())
        except Exception:
            # If the file doesn't exist, return 0
            return 0

    def resetScore(self):
        """
        Helper method used to reset the current score back to 0.

        :return: void method; Does not return anything.
        """
        self.score = 0
        self.questionInfo = [0, 0, 0, 0, 0]
        self.save_score()

    def updateScore(self, points):
        """
        Helper method that adds points to the current score and saves it to the file.

        :param points: int; Points that will be added to the current score.

        :return: void method; Does not return anything.
        """
        self.score += points
        self.save_score()

    def updateNegScore(self, points):
        """
        Helper method that adds points to the current score and saves it to the file.

        :param points: int; Points that will be added to the current score.

        :return: void method; Does not return anything.
        """
        self.score -= points
        self.save_score()


    def save_score(self):
        """
        Helper method that saves the current score to the file.

        :return: void method; Does not return anything.
        """
        with open("score.txt", "w") as file:
            file.write(str(self.score))
            file.write("\n")
            file.write("{}, {}, {}, {}, {}".format(self.questionInfo[0], self.questionInfo[1], self.questionInfo[2],
                                                   self.questionInfo[3], self.questionInfo[4]))

    def load_questionInfo(self):
        """
        Helper method used to load the current score from the file.

        :return: int; The current score loaded from the file.
        """
        try:
            with open("score.txt", "r") as file:
                content = file.readlines()
                questionInfo = [int(x) for x in content[1].strip().split(", ")]
                return questionInfo
        except Exception:
            # If the file doesn't exist, return 0
            return [0, 0, 0, 0, 0]

    def increase_questionCount(self, subject):
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
        numQuestions = self.questionInfo[x]
        numQuestions += 1
        self.questionInfo[x] = numQuestions

    def get_questionInfo(self, subject):
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
