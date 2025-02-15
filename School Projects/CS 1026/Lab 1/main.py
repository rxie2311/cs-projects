# Name: Raymond Xie
# Description: Lab 01
# Date: 2022/09/19

# Q1
answer1 = 5 + 3
answer2 = 7 * 4
print("answer1")
print(answer1)

# Q2
x = 7
print(x)
y = x + 5
# Formatting the print statement
print("x is {} and y is {}".format(x,y))
# Formatting using interpolation
print("x is %d and y is %d" % (x,y))

# Q3
shopName = input("Please enter the shop name: ")
ringQTY = int(input("Please enter ring QTY: "))
glassesQTY = int(input("PLease enter glasses QTY: "))

print("Shop name is {}".format(shopName))
print("Ring QTY is {}".format(ringQTY))
print("Glasses QTY is {}".format(glassesQTY))
print("Inventory Total: {}".format(ringQTY + glassesQTY))