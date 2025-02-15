# Name: Raymond Xie
# Description: Lab 08
# Date: 2022/11/14

# Q1
# Sets
even = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20}
odd = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}
three = {3, 6, 9, 12, 15, 18}
# Dictionary
d = {"even": even, "odd": odd, "three": three}
# For loop that prints out all sets
for i in d:
    print(d[i])

# Q2
f = open("rawdata.txt","r")
incomeDict = {}
countryDict = {}
countryList = []
incomeList = []
initialList = []

for line in f:
    line = line.upper().strip("\n").split(":")
    initialList.append(line[1][0])
    countryList.append(line[1])
    incomeList.append(line[2])

for i in range(0, len(countryList)):
    incomeDict[countryList[i]] = incomeList[i]
    if initialList[i] in countryDict:
        countryDict[initialList[i]].add(countryList[i])
    else:
        countryDict[initialList[i]] = {countryList[i]}

done = False
while not done:
    text = input("Enter an initial or a country name: ")
    text = text.upper()
    if text == "QUIT":
        done = True
    elif text in countryDict:
        print(countryDict[text])
    elif text in incomeDict:
        print(incomeDict[text])
    else:
        print("Does not exist")

# Q3
sentence = "I had such a horrible day It was awful so bad sigh It could not have been worse but actually though it was such a terrible horrible awful bad day"

makeItHappy = {"horrible": "amazing","bad":"good","awful":"awesome","worse":"better","terrible":"great"}

spsentence = sentence.split()
for word in range(0, len(spsentence)):
    # Error 1: Needs another for loop to check the word in spsentence with every dictionary value
    for i in range(0, len(makeItHappy)):
        if spsentence[word] in makeItHappy:
            # Error 2: Needs to call on spsentence[word] instead of just word since word is a number and dictionaries do not have indexes
            spsentence[word] = makeItHappy[spsentence[word]]

newString = ""

for word in spsentence:
    newString = newString + word + " "

print(newString)