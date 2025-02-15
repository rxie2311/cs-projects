# Name: Raymond Xie
# Description: Lab 03
# Date: 2022/10/03

# Q1
n = int(input("How many numbers do you want to use today? "))
if n > 0:
    firstVal = int(input("Enter the first number: "))
    largest = firstVal
    smallest = firstVal
    total = firstVal

    counter = 0
    while counter < (n-1):
        current = int(input("Enter the next number: "))
        total += current
        counter += 1
        if current < smallest:
            smallest = current
        elif current > largest:
            largest = current

    print("The average of the values is: ", total / n)
    print("The smallest of the values is {}".format(smallest))
    print("The largest of the values is {}".format(largest))
    print("The range of the values is {}".format(largest - smallest))
else:
    print("You did not want to use any numbers today.")

# Q2
accountTotal = 50
while accountTotal > 20:
    # Operator is > not =<
    # Need to subtract the value from accountTotal by 1 every time it loops
    accountTotal -= 1
    print(accountTotal)

print("Your account has reached $20")