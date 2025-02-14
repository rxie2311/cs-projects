# Name: Raymond Xie
# Assignment: Assignment 4 - Air Travel
# Date: December 7, 2022

# Imports
from Flight import *
from Airport import *

# allAirports (list) and allFlights (dictionary) containers
allFlights = {}
allAirports = []


# File reader method that reads file, stores values and organizes values in a list of lists
def loadData(airportFile, flightFile):
    # Empty list to store all airports
    airportList = []

    # Use global list allAirports
    global allAirports

    # Also save a dictionary for flight searching
    allAirportsDict = {}

    # Opening and reading the airport file
    try:
        f = open(airportFile, "r")
    except FileNotFoundError:
        # Return False when file is not found
        return False
    # For loop to save all values from the file into the list
    for line in f:
        airportList.append(line)

    # Splitting the list using commas and saving into list
    for i in range(len(airportList)):
        temp = airportList[i]
        # Adding stripped values into the list of lists
        splitAirportList = temp.split(",")
        oneAirport = Airport(splitAirportList[0].strip(), splitAirportList[2].strip(), splitAirportList[1].strip())
        allAirports.append(oneAirport)
        allAirportsDict[splitAirportList[0].strip()] = oneAirport

    # Closing airport file
    f.close()
   
    # Empty list to store all flights
    flightList = []
    # Opening and reading the flight file
    try:
        f = open(flightFile, "r")
    except FileNotFoundError:
        # Return False when file is not found
        return False
    # For loop to save all values from the file into the list
    for line in f:
        flightList.append(line)

    # Transfer flight Class list
    flightClassList = []
    # Splitting the list using commas and saving into list
    for i in range(len(flightList)):
        temp = flightList[i]
        # Adding stripped values into the list of lists
        splitFlightList = temp.split(",")
        oneFlight = Flight(splitFlightList[0].strip(), allAirportsDict[splitFlightList[1].strip()], allAirportsDict[splitFlightList[2].strip()])
        flightClassList.append(oneFlight)

    # Closing flights file
    f.close()

    # Turning flights from list into dictionary
    for originAirport in allAirports:
        # Temp list to store flight objects
        tempFlightList = [flightClass for flightClass in flightClassList if flightClass.getOrigin().getCode() == originAirport.getCode()]
        if len(tempFlightList) > 0:
            # Saving tempFlightList flight object into the dictionary allFlights
            allFlights[originAirport.getCode()] = tempFlightList

    # Return true when everything has finished running
    return True


# Returns the airport object via the code
def getAirportByCode(code):
    # For loop to check all values of allAirports
    for airport in allAirports:
        # If the code matches one of the codes in the allAirports list
        if code == airport.getCode():
            # Returns the object
            return airport

    # Returns -1 if no airport is found to match the code
    return -1


# Finds all flights to and from the selected city
def findAllCityFlights(city):
    # Empty list to store all flights from and to the selected city
    allCityFlights = []
    # Checks for the city name within the allFlights dictionary
    for x in allFlights.values():
        for flight in x:
            # If the city name is in the dictionary value list
            if city.upper() == flight.getOrigin().getCity().upper() or city.upper() == flight.getDestination().getCity().upper():
                # Adds that specific flight into the list
                allCityFlights.append(flight)

    # Returning the list
    return allCityFlights


# Finds all flights to and from the selected country
def findAllCountryFlights(country):
    # Empty list to store all flights from and to the selected Country
    allCountryFlights = []
    # Checks for the city name within the allFlights dictionary
    for x in allFlights.values():
        for flight in x:
            # If the country name is in the dictionary value list
            if country.upper() == flight.getOrigin().getCountry().upper() or country.upper() == flight.getDestination().getCountry().upper():
                # Adds that specific flight into the list
                allCountryFlights.append(flight)

    # Returning the list
    return allCountryFlights


# Finding if there is a direct flight from City A to City B, or finding a hop from City A to X and X to City B
def findFlightBetween(origAirport, destAirport):
    # Checking if there is a direct flight from City A to City B
    for flight in allFlights[origAirport.getCode()]:
        # If the origin and destination airport are both in the flight
        if destAirport.getCode() == flight.getDestination().getCode():
            return "Direct Flight: " + flight.getOrigin().getCode() + " to " + flight.getDestination().getCode()

    # Checking if there is set of single-hop flight from origAirport to destAirport
    singleHopCityList = []
    for flight in allFlights[origAirport.getCode()]:
        if destAirport.getCode() != flight.getDestination().getCode():
            for flightHop in allFlights[flight.getDestination().getCode()]:
                if destAirport.getCode() == flightHop.getDestination().getCode():
                    singleHopCityList.append(flightHop.getOrigin().getCode())
                    break

    # Returns the set if there is more than 0 flights in it
    if len(singleHopCityList) > 0:
        return set(singleHopCityList)
    else:
        # Returns -1 if there is no other flights in the set
        return -1


# Take the given Flight object and look for the Flight object representing the return flight from that given flight
def findReturnFlight(firstFlight):
    # Finds return flight using destination and flight code
    for flight in allFlights[firstFlight.getDestination().getCode()]:
        if firstFlight.getOrigin().getCode() == flight.getDestination().getCode():
            # Returns the flight if a return flight is found
            return flight
    # Returns -1 if search is unsuccessful
    return -1
