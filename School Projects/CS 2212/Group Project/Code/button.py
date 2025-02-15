class Button():
	"""
	The Button class represents the GUI buttons and how to modify them and check for input.
	"""

	def __init__(self, image, pos, text_input, font, base_color, hovering_color):
		"""
		Constructor that creates a new button.

		:param image: The image for the button.
		:param pos: The position of the button on the screen.
		:param text_input: The text on the button.
		:param font: The font for the text on the button.
		:param base_color: The color of the button.
		:param hovering_color: The color the button will show as when hovered over by a mouse.

		:return: void method; Does not return anything.
		"""

		self.image = image
		self.x_pos = pos[0]
		self.y_pos = pos[1]
		self.font = font
		self.base_color, self.hovering_color = base_color, hovering_color
		self.text_input = text_input
		self.text = self.font.render(self.text_input, True, self.base_color)
		if self.image is None:
			self.image = self.text
		self.rect = self.image.get_rect(center=(self.x_pos, self.y_pos))
		self.text_rect = self.text.get_rect(center=(self.x_pos, self.y_pos))

	def update(self, screen):
		"""
		Helper method that updates the screen.

		:param screen: The screen for the GUI.

		:return: void method; Does not return anything.
		"""

		if self.image is not None:
			screen.blit(self.image, self.rect)
		screen.blit(self.text, self.text_rect)

	def checkForInput(self, position):
		"""
		Helper method that checks if the button was clicked.

		:param position: Position of the button on the screen.

		:return: (Boolean): True if input was detected, False otherwise.
		"""

		if position[0] in range(self.rect.left, self.rect.right) and position[1] in range(self.rect.top, self.rect.bottom):
			return True
		return False

	def changeColor(self, position):
		"""
		Helper method that changes the button's color when hovered over with a mouse.

		:param position: Position of the button on the screen.

		:return: void method; Does not return anything.
		"""

		if position[0] in range(self.rect.left, self.rect.right) and position[1] in range(self.rect.top, self.rect.bottom):
			self.text = self.font.render(self.text_input, True, self.hovering_color)
		else:
			self.text = self.font.render(self.text_input, True, self.base_color)