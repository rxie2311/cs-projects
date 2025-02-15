# Name: Raymond Xie
# Assignment: Assignment 2 - Pizza Ordering Service
# Date: October 26, 2022

# Importing all fucntions from pizzaReceipt
from pizzaReceipt import *

# TOPPINGS constant - lists all available topings in the tuple
TOPPINGS = ("ONION", "TOMATO", "GREEN PEPPER", "MUSHROOM", "OLIVE", "SPINACH", "BROCCOLI", "PINEAPPLE", "HOT PEPPER", "PEPPERONI", "HAM", "BACON", "GROUND BEEF", "CHICKEN", "SAUSAGE")

# pizzaOrder - empty list that will hold the entire order
pizzaOrder = ()

# Boolean variable that will change if the user does not want to order anymore
contOrder = True

# Ask the user if they wish to order a pizza
answer = input("Do you want to order a pizza? ")

# Ignores cases by changing the user's answer into all lowercase letters
if answer.lower() == "no" or answer.lower() == "q":
    generateReceipt(pizzaOrder)  # Returns the empty list
    contOrder = False # Sets the boolean to False so it skips over the while loop

# while loop that locks the user into a loop until they do not want to order anymore
while contOrder == True:
    correctSize = False # Changes to True when the user enters a valid size

    while correctSize == False:
        size = input("Choose a size: S, M, L or XL: ")  # Asks the user for a size
        if size.upper() == "S" or size.upper() == "M" or size.upper() == "L" or size.upper() == "XL":
            correctSize = True  # Breaks the user out of the loop when a correct size is entered
        else:
            del size  # Clears the variable if it is not a valid size and locks the user in a loop until the correct size is entered

    # Saves the size into the empty list
    pizzaOrder = pizzaOrder + (size,)

    correctTop = False # Changes to True when the user is done ordering
    validTop = True # Changes to False when the user enters an invalid topping
    userToppings = [] # Empty list that will store all toppings the user enters

    while correctTop == False:
        # Asks the user for their choice of toppings
        topping = input('Type in one of our toppings to add it to your pizza. To see the list of toppings, enter "LIST". When you are done adding toppings, enter "X"\n\n')
        # If the user types 'LIST'
        if topping.upper() == "LIST":
            print(TOPPINGS) # Prints the tuple for the user to see
        # If the user types 'X'
        elif topping.upper() == "X":
            correctTop = True # Sets the boolean to True and breaks out of the while loop
        # If none of the above are inputted
        else:
            # For loop to check if the topping entered matches one in the tuple
            for t in range(0, len(TOPPINGS)):
                if topping.upper() == TOPPINGS[t]:
                    userToppings.append(topping) # Adds the topping to the list
                    validTop = True # Sets validTop back to True since the topping entered was valid
                    break
                else:
                    validTop = False # Sets validTop to false since the topping entered was invalid

            # Prints out invalid topping if the topping entered does not match any of the ones in the tuple
            if validTop == False:
                print("Invalid topping")

    # Adding topping tuple to the pizzaOrder list and sending it over to generateReceipt
    pizzaOrder = pizzaOrder + (userToppings,)

    # Asking the user if they want to continue ordering
    cont = input("Do you want to continue ordering? ")
    if cont.lower() == "no" or cont.lower() == "q":
        generateReceipt(pizzaOrder) # Sends the list to generateReceipt
        pizzaOrder = tuple() # Clears the tuple
        break # Exits out of the while loop
    else:
        generateReceipt(pizzaOrder)
        pizzaOrder = tuple()

# Spacing
print(" ")
# Calling printReceipt to print out the final receipt
printReceipt()