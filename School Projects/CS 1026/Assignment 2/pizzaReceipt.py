# Name: Raymond Xie
# Assignment: Assignment 2 - Pizza Ordering Service
# Date: October 26, 2022

# Empty lists
pizzaReceipt = []
pizzaToppings = []

# generateReceipt function
def generateReceipt(pizzaOrder):
    if len(pizzaOrder) == 0:
        print("You did not order anything") # Prints if the customer did not order
    else:
        pizzaReceipt.append(pizzaOrder[0])  # Adds the pizza order into the list
        pizzaToppings.append(pizzaOrder[1])
        return pizzaReceipt, pizzaToppings  # Saves the list and returns it


# printReceipt function
def printReceipt():
    # Variables
    counter = 0
    total = 0
    toppingAmount = 0

    # Print statement
    print("Your order:")

    for i in range(0, len(pizzaReceipt)):
        counter+= 1
        # Checking the sizes of the pizza and adding the correct values
        # SMALL PIZZA
        if pizzaReceipt[i].upper() == "S":
            print("Pizza " + str(counter) + ": " + pizzaReceipt[i].upper() + "                    7.99")
            total = total + 7.99 # Adding base price to total amount

            # Printing toppings
            for j in range(counter-1, counter): # Takes counter-1 and counter as the range so it isolates the location at where the topping is stored
                for k in pizzaToppings[j]:
                    print("- " + k.upper()) # Prints out the toppings one by one
                    toppingAmount = len(pizzaToppings[j]) # Saves the length of the list containing the toppings for later use

            # Checking if there are more than 3 toppings using length we saved earlier
            if (toppingAmount > 3):
                total = total + (0.50*(toppingAmount-3))  # Adding extra topping price to total amount
                bonusTop = round(0.50*(toppingAmount-3), 2)
                print("Extra Topping (S)             " + str(bonusTop))

        # MEDIUM PIZZA
        elif pizzaReceipt[i].upper() == "M":
            print("Pizza " + str(counter) + ": " + pizzaReceipt[i].upper() + "                    9.99")
            total = total + 9.99

            # Printing toppings
            for j in range(counter - 1, counter):  # Takes counter-1 and counter as the range so it isolates the location at where the topping is stored
                for k in pizzaToppings[j]:
                    print("- " + k.upper())
                    toppingAmount = len(pizzaToppings[j])

            # Checking if there are more than 3 toppings
            if (toppingAmount > 3):
                total = total + (0.75*(toppingAmount-3))  # Adding extra topping price to total amount
                bonusTop = round(0.75 * (toppingAmount - 3), 2)
                print("Extra Topping (M)             " + str(bonusTop))

        # LARGE PIZZA
        elif pizzaReceipt[i].upper() == "L":
            print("Pizza " + str(counter) + ": " + pizzaReceipt[i].upper() + "                   11.99")
            total = total + 11.99

            # Printing toppings
            for j in range(counter - 1, counter):  # Takes counter-1 and counter as the range so it isolates the location at where the topping is stored
                for k in pizzaToppings[j]:
                    print("- " + k.upper())
                    toppingAmount = len(pizzaToppings[j])

            # Checking if there are more than 3 toppings
            if (toppingAmount > 3):
                total = total + (1.00*(toppingAmount-3))  # Adding extra topping price to total amount
                bonusTop = round(1.00 * (toppingAmount - 3), 2)
                print("Extra Topping (L)             " + str(bonusTop))

        # XL PIZZA
        elif pizzaReceipt[i].upper() == "XL":
            print("Pizza " + str(counter) + ": " + pizzaReceipt[i].upper() + "                  13.99")
            total = total + 13.99

            # Printing toppings
            for j in range(counter - 1, counter):  # Takes counter-1 and counter as the range so it isolates the location at where the topping is stored
                for k in pizzaToppings[j]:
                    print("- " + k.upper())
                    toppingAmount = len(pizzaToppings[j])

            # Checking if there are more than 3 toppings
            if (toppingAmount > 3):
                total = total + (1.25*(toppingAmount-3))  # Adding extra topping price to total amount
                bonusTop = round(1.25 * (toppingAmount - 3), 2)
                print("Extra Topping (XL)            " + str(bonusTop))

    # Calculating tax (13%)
    tax = round(total * 0.13, 2)
    print("Tax:                          " + str(tax))

    # Print Total
    total = round(total + tax, 2)
    print("Total:                       " + str(total))