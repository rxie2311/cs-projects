from player import Player

def load_players(filename="accounts.txt"):
    """
    Load player profiles from a file, including avatar ID.

    :param filename: The player file where all players are stored.

    :return: An array containing all the players on the player file.
    """

    players = []
    try:
        with open(filename, 'r') as file:
            lines = [line.strip() for line in file.readlines()]
            for i in range(0, len(lines), 5):  # Adjusted to account for the extra line per player
                username, password = lines[i].split(", ")
                gameInfo = list(map(int, lines[i+1].split(", ")))
                questionInfo = list(map(int, lines[i+2].split(", ")))
                achievements = list(map(int, lines[i+3].split(", ")))
                avatarID = lines[i+4]  # Retrieve the avatar ID
                players.append(Player(username, password, gameInfo, questionInfo, achievements, avatarID))
    except FileNotFoundError:
        print(f"No such file: {filename}")
    return players

def save_players(players, filename="accounts.txt"):
    """
    Helper method that saves all player profiles to a file, including avatar ID.

    :param players: The player array containing all player files.
    :param filename: The player file where all players are stored.

    :return: void method; Does not return anything.
    """
    with open(filename, 'w') as file:
        for player in players:
            data = [
                f"{player.username}, {player.password}",
                ", ".join(map(str, player.gameInfo)),
                ", ".join(map(str, player.questionInfo)),
                ", ".join(map(str, player.achievements)),
                player.avatarID  # Save the avatar ID
            ]
            file.write("\n".join(data) + "\n")

def update_player(players, username, high_score=None, achievements_add=None, achievements_remove=None, avatarID=None):
    """
    Helper method that updates a player's profile based on provided parameters, including avatar ID.

    :param players: The player array containing all player files.
    :param username: The player's new username.
    :param high_score: The player's new highscore.
    :param achievements_add: The player's new achievements.
    :param achievements_remove: The achievements to be removed from the player.
    :param avatarID: The player's avatar ID.

    :return: True if successfully updated, False otherwise.
    """

    for player in players:
        if player.username == username:
            if high_score is not None:
                player.setHighScore(int(high_score))
            if achievements_add:
                for achievement in achievements_add:
                    player.addAchievement(achievement)
            if achievements_remove:
                for achievement in achievements_remove:
                    player.removeAchievement(achievement)
            if avatarID is not None:
                player.avatarID = avatarID  # Update the avatar ID if provided
            return True  # Successfully updated
    return False  # Player not found

def get_player(players, username):
    """
    Helper method that returns a player via username.

    :param players: The player array containing all player files.
    :param username: The player's username.

    :return: Returns the player if the username matches one in the files, returns None if nothing is found.
    """

    for player in players:
        if player.username == username:
            return player
    return None
