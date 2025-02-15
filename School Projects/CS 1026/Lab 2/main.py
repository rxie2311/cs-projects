# Name: Raymond Xie
# Description: Lab 02
# Date: 2022/09/26

# Q1
age = int(input("Enter your age: "))

if age >= 9:
    height = float(input("Enter your height in cm: "))
    if height > 130:
        print("You may go on this ride!")
    else:
        print("You are too short for this ride.")
else:
    print("You are too young for this ride.")

# Q2
IDEAL_CREDIT_SCORE = 720

userScore = int(input("Please enter your credit score: "))
housePrice = int(input("Please enter the price of the house: "))

if userScore >= IDEAL_CREDIT_SCORE:
    # Error 1: operation sign needs to be >= and not =>
    downPayment = 0.1 * housePrice
elif userScore < IDEAL_CREDIT_SCORE and userScore > 600:
    # Error 2: else if is elif, not else if
    # Error 3: 600 cannot have quotation marks around it for it to be compared to an integer
    downPayment = 0.2 * housePrice
else:
    # Error 4: downPayment needs to be indented
    downPayment = 0.3 * housePrice

print("Your down payment is: ${}".format(downPayment))