# Import
from Airport import *


# Flight Class
class Flight:
    # Initializing function
    def __init__(self, flightNo, origin, destination):
        # Checks if origin and destination are Airport objects
        if isinstance(origin, Airport) == False or isinstance(destination, Airport) == False:
            # If they are not Airport objects, raises a type error
            raise TypeError("The origin and destination must be Airport objects")

        self.flightNo = flightNo
        self.origin = origin
        self.destination = destination

    # Repr function
    def __repr__(self):
        # If isDomesticFlight returns true
        if self.isDomesticFlight() == True:
            # Returns domestic at the end
            return "Flight: " + self.flightNo + " from " + self.origin.getCity() + " to " + self.destination.getCity() + " {domestic}"
        # If isDomesticFlight returns false
        else:
            # Returns international at the end
            return "Flight: " + self.flightNo + " from " + self.origin.getCity() + " to " + self.destination.getCity() + " {international}"

    # Eq function
    def __eq__(self, other):
        # Checks if the other variable isn't a flight object
        if isinstance(other, Flight) == False:
            # Raises a type error
            return False
        # Returns true if both flights are considered the same
        return (self.getOrigin().getCode() == other.getOrigin().getCode()) and (self.getDestination().getCode() == other.getDestination().getCode())

    # Getter functions
    def getFlightNumber(self):
        return self.flightNo

    def getOrigin(self):
        return self.origin

    def getDestination(self):
        return self.destination

    # Setter functions
    def setOrigin(self, origin):
        self.origin = origin

    def setDestination(self, destination):
        self.destination = destination

    # Checks if flight is flying within the country
    def isDomesticFlight(self):
        # The origin and destination are in the same country
        if self.origin.getCountry() == self.destination.getCountry():
            return True
        # The origin and destination are in different countries
        else:
            return False
