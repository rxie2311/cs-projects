# Name: Raymond Xie
# Assignment: Assignment 3 - University Rankings
# Date: November 9, 2022

# Main function: getInformation(selectedCountry, rankingFileName, capitalsFileName)
def getInformation(selectedCountry, rankingFileName, capitalsFileName):
    # Creating an output.txt file only if the program detects that it does not exist
    f = open('output.txt', "w")

    # Try-except to catch a missing file error
    try:
        # Loading files using the load functions below using try-except to catch errors
        rankingList = loadCSVDataTopUni(rankingFileName)
        capitalList = loadCSVDataCapitals(capitalsFileName)
    except FileNotFoundError:
        # Writes an error in the file if a file is missing
        f.write("Error: File not found!")
        f.close()
        quit()

    # Closing the file after the try-except to reopen as append mode
    f.close()
    outputFile = open('output.txt', "a")

    # 1: University count
    # Using the list length tells us how many universities there are in the file
    outputFile.write("Total number of universities => " + str(len(rankingList)))

    # 2: Available countries
    # Using a for loop to run through all countries in the list and add them if the country isn't already in the list
    outputFile.write("\n\nAvailable countries => ")
    # Empty list to store countries with no dupes (reference list later)
    countries = []
    # Duplicate checker
    for i in range(len(rankingList)):
        for j in range(len(rankingList[i])):
            if j == 2:
                # Checks to make sure the country name isn't already in the list
                if rankingList[i][j] not in countries:
                    # Adds the non-dupe country into the list for reference
                    countries.append(rankingList[i][j])
                    # Writes the country name into the file
                    outputFile.write(rankingList[i][j].upper() + ", ")

    # 3: Available continents
    outputFile.write("\n\nAvailable continents => ")
    # Empty list to store continents with no dupes (reference list later)
    continents = []
    # Duplicate checker
    for k in range(len(capitalList)):
        for l in range(len(capitalList[k])):
            if l == 2:
                # Checks to make sure the country name isn't already in the list
                if capitalList[k][l] not in continents:
                    capitalList[k][l].replace("\n", "")
                    # Adds the non-dupe continent into the list for reference
                    continents.append(capitalList[k][l])
                    # Writes the continent name into the file
                    outputFile.write(capitalList[k][l].upper() + ", ")

    # 4: University with top international rank
    # Empty list to store all universities that are in the selected country
    ranks = []
    # For loop to check individual lists in the list
    for m in range(len(rankingList)):
        for n in range(len(rankingList[m])):
            if n == 2:
                # Checks if the country name matches with the selected country
                if selectedCountry.upper() == rankingList[m][n].upper():
                    # Adds the university into the ranks list
                    ranks.append(rankingList[m])

    # Saves the world rank of the first university on the list as the highest since the list is ordered by world rank
    outputFile.write("\n\nAt international rank => " + ranks[0][0] + " the university name is => " + ranks[0][1].upper())

    # 5: University with top national rank
    # Defaults the first university on the list as the highest
    highestRank = int(ranks[0][3])
    uniName = ranks[0][1]
    # For loop to check which national rank is the highest
    for o in range(len(ranks)):
        for p in range(len(ranks[o])):
            if p == 3:
                # Converts the two strings into ints and compares to see which one is higher (smaller number)
                if int(ranks[o][p]) < highestRank:
                    # Replaces the old highest rank with the new highest rank
                    highestRank = int(ranks[o][p])
                    # Saves the university name as well for later
                    uniName = ranks[o][p-2]

    # Writes to the file
    outputFile.write("\n\nAt national rank => " + str(highestRank) + " the university name is => " + uniName.upper())

    # 6: The average score
    # Average variable
    average = 0
    # Adding up the scores
    for q in range(len(ranks)):
        for r in range(len(ranks[q])):
            if r == 4:
                # Adds the scores to existing average to total up all scores
                average = float(ranks[q][r]) + average

    # Calculating the rest of the average
    average = average / len(ranks)
    # Rounding to two decimal places
    average = round(average, 2)

    # Writing to file
    outputFile.write("\n\nThe average score => " + str(average) + "%")

    # 7: Continent relative score
    # Empty values
    continent = ""
    countries = []
    continentUni = []
    # For loop to check what continent the country is in
    for i in range(len(capitalList)):
        for j in range(len(capitalList[i])):
            if j == 0:
                if selectedCountry.upper() == capitalList[i][j].upper():
                    continent = capitalList[i][2].upper()

    # For loop to store all countries that are in the continent
    for i in range(len(capitalList)):
        for j in range(len(capitalList[i])):
            if j == 2:
                # If the continent matches the continent of that specific list
                if continent.upper() == capitalList[i][j].upper():
                    # Checking for duplicates
                    if capitalList[i][0] not in countries:
                        # Saves the country name in countries list
                        countries.append(capitalList[i][0])

    # For loop to store all universities with the countries in
    for i in range(len(rankingList)):
        for j in range(len(rankingList[i])):
            if j == 2:
                # Checking if university country matches all country names in the continent
                for k in range(len(countries)):
                    # If the country names match
                    if countries[k].upper() == rankingList[i][j].upper():
                        # University info is saved
                        continentUni.append(rankingList[i])

    # Math
    # Empty variables
    totalScore = 0.0
    averageScore = 0.0
    continentAverage = 0.0
    # The highest score is automatically set as the first university since the order is ranked by score
    highestScore = float(continentUni[0][4])
    # Total scores
    for i in range(len(continentUni)):
        for j in range(len(continentUni[i])):
            if j == 4:
                totalScore = totalScore + float(continentUni[i][j])

    # Calculating average
    averageScore = totalScore / len(continentUni)

    # Calculating continent average
    continentAverage = (averageScore / highestScore) * 100.0

    # Rounding
    averageScore = round(averageScore, 2)
    continentAverage = round(continentAverage, 2)

    # Writing to file
    outputFile.write("\n\nThe relative score to the top university in " + continent + " is => (" + str(averageScore) + " / " + str(highestScore) + ") x 100% = " + str(continentAverage) + "%")

    # 8: Capital city
    # Capital string to hold the capital of the country for later use
    capital = ""

    # For loop to match country to capital
    for i in range(len(capitalList)):
        for j in range(len(capitalList[i])):
            if j == 0:
                # Checking if country names match
                if selectedCountry.upper() == capitalList[i][j].upper():
                    # Saves the capital name
                    capital = capitalList[i][1].upper()

    # Writing to file
    outputFile.write("\n\nThe capital is => " + capital)

    # 9: Universities that hold the capital name
    # Empty list to store universities that contain the capital name
    capitalName = []

    # For loop to find university names that match the capital name
    for i in range(len(ranks)):
        for j in range(len(ranks[i])):
            if j == 1:
                if capital.upper() in ranks[i][j].upper():
                    capitalName.append(ranks[i][j].upper())

    # Counter variable for numbering
    counter = 1
    # Writing into the file
    outputFile.write("\n\nThe universities that contain the capital name =>")
    for i in range(len(capitalName)):
        outputFile.write("\n        #" + str(counter) + " " + capitalName[i])
        counter += 1

    # Close the file at the end
    outputFile.close()

# Load CSV File for TopUni.csv
def loadCSVDataTopUni(filename):
    # List to store all CSV data values
    topUniList = []
    fileContent = open(filename, "r", encoding='utf8')

    # Saving all values of the file into the list
    for line in fileContent:
        topUniList.append(line)

    # Getting rid of useless headers (1st line)
    topUniList.pop(0)
    # New list to store split values
    splitTopUniList = []
    # Splitting the list using commas and saving into list of lists
    for i in range(len(topUniList)):
        temp = topUniList[i]
        splitTopUniList.append(temp.split(","))

    # Removing useless values from the list (Quality of Education, Alumni, Quality of Faculty, Research)
    for j in range(len(splitTopUniList)):
        for k in range(len(splitTopUniList[j])):
            # Targets index positions with useless values
            if k == 4 or k == 5 or k == 6 or k == 7:
                # Replaces useless values with 'temp' for easier removal later
                splitTopUniList[j][k] = "temp"

    # Removes all instances of 'temp' from the list
    for j in range(len(splitTopUniList)):
        # Uses a while loop to keep removing 'temp' until the list no longer contains 'temp'
        while "temp" in splitTopUniList[j]:
            splitTopUniList[j].remove("temp")

    # Removes the \n at the end of the lists
    for j in range(len(splitTopUniList)):
        for k in range(len(splitTopUniList[j])):
            while "\n" in splitTopUniList[j][k]:
                splitTopUniList[j][k] = splitTopUniList[j][k].replace("\n", "")

    # Returns the list
    return splitTopUniList

# Load CSV File for capitals.csv
def loadCSVDataCapitals(filename):
    # List to store all CSV data values
    capitalsList = []
    fileContent = open(filename, "r", encoding='utf8')

    # Saving all values of the file into the list
    for line in fileContent:
        capitalsList.append(line)

    # Getting rid of useless headers (1st line)
    capitalsList.pop(0)
    # New list to store split values
    splitCapitalsList = []
    # Splitting the list using commas and saving into list of lists
    for i in range(len(capitalsList)):
        temp = capitalsList[i]
        splitCapitalsList.append(temp.split(","))

    # Removing useless values from the list (Latitude, Longitude, Country Code)
    for j in range(len(splitCapitalsList)):
        for k in range(len(splitCapitalsList[j])):
            # Targets index positions with useless values
            if k == 2 or k == 3 or k == 4:
                # Replaces useless values with 'temp' for easier removal later
                splitCapitalsList[j][k] = "temp"

    # Removes all instances of 'temp' from the list
    for j in range(len(splitCapitalsList)):
        # Uses a while loop to keep removing 'temp' until the list no longer contains 'temp'
        while "temp" in splitCapitalsList[j]:
            splitCapitalsList[j].remove("temp")

    # Removes the \n at the end of the lists
    for j in range(len(splitCapitalsList)):
        for k in range(len(splitCapitalsList[j])):
            while "\n" in splitCapitalsList[j][k]:
                splitCapitalsList[j][k] = splitCapitalsList[j][k].replace("\n", "")

    # Returns the list
    return splitCapitalsList