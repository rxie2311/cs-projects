# Name: Raymond Xie
# Description: Lab 07
# Date: 2022/11/07

# Q1
values = [1, 2, 3, 4, 5, "hello", 6, 7, 8, 9, "10"]

for cur in values:
    print("The value is :", values[cur])
    if type(values[cur]) == str:
        # Raise exception to print out "This is a string"
        raise Exception("This is a string!")

# Q3
try:
    filename = input("Enter filename: ")
    infile = open(filename, "r")
# Exception 1: File not found error, except creates a new file that matches the filename the user inputs
except FileNotFoundError:
    f = open(filename + ".txt", "x")
    f.close()
    try:
        infile = open(filename + ".txt", "r")
        line = infile.readline()
        value = int(line)
    # Exception 2: Value Error because there are no values in the file
    except ValueError:
        k = open(filename + ".txt", "w")
        k.write("10")
        k.close()
        j = open(filename + ".txt", "r")
        line = j.readline()
        value = int(line)