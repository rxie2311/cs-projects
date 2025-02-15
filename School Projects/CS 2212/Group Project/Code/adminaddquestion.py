import pygame
import sys
from question import *  # Adjust this import based on your project's structure

pygame.init()

screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("Admin Add Question")

color_inactive = pygame.Color('lightskyblue3')
color_active = pygame.Color('dodgerblue2')
font = pygame.font.Font(None, 32)
bg = pygame.image.load("bg3.png")
class InputBox:
    def __init__(self, x, y, w, h, text='', label=''):
        self.rect = pygame.Rect(x, y, w, h)
        self.color = color_inactive
        self.text = text
        self.txt_surface = font.render(text, True, self.color)
        self.active = False
        self.label = label

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.rect.collidepoint(event.pos):
                self.active = not self.active
            else:
                self.active = False
            self.color = color_active if self.active else color_inactive
        if event.type == pygame.KEYDOWN:
            if self.active:
                if event.key == pygame.K_RETURN:
                    print(self.text)
                elif event.key == pygame.K_BACKSPACE:
                    self.text = self.text[:-1]
                else:
                    self.text += event.unicode
                self.txt_surface = font.render(self.text, True, pygame.Color('black'))

    def update(self):
        width = max(200, self.txt_surface.get_width()+10)
        self.rect.w = width

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect, 2)
        screen.blit(self.txt_surface, (self.rect.x+5, self.rect.y+5))
        label_surface = font.render(self.label, True, pygame.Color('black'))
        screen.blit(label_surface, (self.rect.x - label_surface.get_width() - 10, self.rect.y + 5))

class Button:
    def __init__(self, x, y, w, h, text=''):
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        self.color = pygame.Color('grey12')

    def draw(self, screen):
        pygame.draw.rect(screen, self.color, self.rect)
        txt_surface = font.render(self.text, True, pygame.Color('white'))
        screen.blit(txt_surface, (self.rect.x + 20, self.rect.y + 10))

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.rect.collidepoint(event.pos):
                return True  # Button click
        return False

def main():
    clock = pygame.time.Clock()
    input_boxes = [
        InputBox(400, 50, 140, 32, label='Subject'),
        InputBox(400, 100, 140, 32, label='Points'),
        InputBox(400, 150, 140, 32, label='Question'),
        InputBox(400, 200, 140, 32, label='Answer'),
        InputBox(400, 250, 140, 32, label='Tutorial')
    ]
    button = Button(350, 400, 100, 50, 'Add')
    questionFile = "question.csv"
    questionFactory = QuestionFactory(questionFile)

    done = False
    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            for box in input_boxes:
                box.handle_event(event)
            if button.handle_event(event):
                subject = input_boxes[0].text.strip()
                questionPoints = input_boxes[1].text.strip()  # Temporarily hold as string for validation
                questionStr = input_boxes[2].text.strip()
                answerStr = input_boxes[3].text.strip()
                tutorial = input_boxes[4].text.strip()
                if all([subject, questionPoints, questionStr, answerStr, tutorial]):
                    try:
                        questionPoints = int(questionPoints)
                        print(subject)
                        print(questionPoints)
                        print(questionStr)
                        print(answerStr)
                        print(tutorial)
                        questionFactory.addQuestion(subject, questionPoints, questionStr, answerStr, tutorial, "questions.csv")
                        print("Question added successfully.")
                    except ValueError:
                        print("Error")
                else:
                    print("Please fill in all fields.")

        screen.blit(bg, (0, 0))
        for box in input_boxes:
            box.draw(screen)
        button.draw(screen)

        pygame.display.flip()
        clock.tick(30)

if __name__ == '__main__':
    main()
