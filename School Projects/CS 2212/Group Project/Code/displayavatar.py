
import pygame
from player import currentUser  # Assuming currentUser() is defined to get the current user object

class DisplayAvatar:
    """
    The DisplayAvatar class helps display the user's avatar on screen.
    """

    def __init__(self, screen):
        """
        Constructor to load the user's avatar on screen.

        :param screen: The screen to be displayed on.

        :return: void method; Does not return anything.
        """

        self.screen = screen
        # Load avatar images into a dictionary for easy access
        self.avatar_images = {i: pygame.image.load(f"avatar{i}.png") for i in range(10)}

    def display(self):
        """
        Helper method that displays the user's avatar on the screen.

        :return: void method; Does not return anything.
        """

        # Retrieve current user's avatar ID
        avatar_id = currentUser("accounts.txt").getAvatarID()

        # Fetch the appropriate avatar image based on the current user's avatar ID
        avatar_image = self.avatar_images[avatar_id]

        # Define the new size for the avatar image
        # For example, to scale the image to 100x100 pixels
        new_size = (350, 350)

        # Scale the avatar image to the new size
        scaled_avatar_image = pygame.transform.scale(avatar_image, new_size)

        # Adjust the position as needed for where you want the avatar to display on the screen
        position = (600, 180)  # Example position

        # Display the scaled avatar image at the specified position on the screen
        self.screen.blit(scaled_avatar_image, position)