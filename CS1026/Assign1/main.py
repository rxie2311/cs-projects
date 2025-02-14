# Name: Raymond Xie
# Assignment: Assignment 1 - Inflation Rate Calculator
# Date: October 5, 2022

# Print statements to take user input and store them in variables
year = input("Please enter the year that you want to calculate the personal interest rate for: ")
expenditure = int(input("Please enter the number of expenditure categories: "))

# Creating variables to store total expense values that the user inputs
prevYear = 0
currentYear = 0

# For loop to repeat the input process based on the number of expenditure categories inputted by the user
# Also saves the user input into the lists
for i in range(expenditure):
    prevYear = prevYear + (int(input("Please enter expenses for previous year: ")))
    currentYear = currentYear + (int(input("Please enter expenses for year of interest: ")))

# Inflation calculation using formula
infRate = ((currentYear - prevYear) / currentYear) * 100
print("Personal inflation rate for " + year + " is " + str(infRate) + "%")

# If statement to print the type of inflation based on the percentage
# If the inflation rate number is lower than 3
if infRate < 3:
    print("Type of Inflation: Low")
# If the inflation rate number is greater than or equal to 3 but less than 5
elif 3 <= infRate < 5:
    print("Type of Inflation: Moderate")
# If the inflation rate number is greater than or equal to 5 but less than 10
elif 5 <= infRate < 10:
    print("Type of Inflation: High")
# If the inflation rate number is greater than 10
else:
    print("Type of Inflation: Hyper")