from player import Player
from achievements import isDone

class Avatar:
    """
    The Avatar class creates a new avatar object.
    """

    def __init__(self, player: Player):
        """
        Constructor creates a new avatar for the player.

        :param player: The player profile the avatar will be linked to.

        :return: void method; Does not return anything.
        """

        self.player = player
        self.decoratedAvatar = DefaultAvatar()

    def display(self):
        """
        Helper method that displays the avatar on screen with or without customizations.

        :return: void method; Does not return anything.
        """

        # Check achievements to unlock items in inventory
        self.checkInventoryUnlock()

        # Display inventory items
        self.decoratedAvatar.display()

    def checkInventoryUnlock(self):
        """
        Check achievements to unlock items in inventory.

        :return: void method; Does not return anything.
        """
        achievements = self.player.getAchievements()
        unlockedItem = set()

        # Determine unlocked items based on achievements
        for achievement in achievements:
            if achievement == 1:
                unlockedItem.add("pencil1")
            elif achievement == 2:
                unlockedItem.add("crayon1")
            elif achievement == 3:
                unlockedItem.add("candy1")
            elif achievement == 4:
                unlockedItem.add("calculator1")
            elif achievement == 5:
                unlockedItem.add("microscope1")
            elif achievement == 6:
                unlockedItem.add("globe1")
            elif achievement == 7:
                unlockedItem.add("hat1")
            elif achievement == 8:
                unlockedItem.add("notebook1")
            elif achievement == 9:
                unlockedItem.add("trophy1")

        # Update inventory with unlocked items
        self.decoratedAvatar = InventoryDecorator(self.decoratedAvatar, unlockedItem)

class DefaultAvatar:
    """
    The DefaultAvatar class creates a new default avatar.
    """

    def display(self):
        pass

class AvatarDecorator:
    """
    The AvatarDecorator class creates a new decorated avatar.
    """

    def __init__(self, decoratedAvatar: DefaultAvatar):
        """
        Constructor creates a new decorated avatar.

        :param decoratedAvatar: The decorated avatar to be displayed.

        :return: void method; Does not return anything.
        """

        self.decoratedAvatar = decoratedAvatar

    def display(self):
        """
        Helper method to display the current avatar.

        :return: void method; Does not return anything.
        """

        self.decoratedAvatar.display()

class InventoryDecorator(AvatarDecorator):
    """
    The InventoryDecorator class creates a new inventory object.
    """

    def __init__(self, decoratedAvatar: DefaultAvatar, inventoryItems):
        """
        Constructor creates a new inventory object with the unlocked items and the avatar.

        :param decoratedAvatar: The decorated avatar to be displayed.
        :param inventoryItems: The inventory items the user has unlocked.

        :return: void method; Does not return anything.
        """

        super().__init__(decoratedAvatar)
        self.inventoryItems = inventoryItems

    def display(self):
        """
        Helper method that displays the inventory with items and the avatar.

        :return: void method; Does not return anything.
        """

        super().display()
        print("Inventory:")
        for item in self.inventoryItems:
            print(item)

# Usage example
if __name__ == "__main__":
    # Create a player instance (assuming you have a valid Player object)
    player = Player("username", "password", [0, 0, 0], [0, 0, 0, 0, 0], [])

    # Create an Avatar instance for the player
    avatar = Avatar(player)

    # Display the avatar and inventory
    avatar.display()
