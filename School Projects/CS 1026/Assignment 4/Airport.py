# Airport Class
class Airport:
    # Initializing function
    def __init__(self, code, city, country):
        self.code = code
        self.city = city
        self.country = country

    # Repr function
    def __repr__(self):
        # Returns formatted code
        return self.code + " (" + self.city + ", " + self.country + ")"

    # Getter functions
    def getCode(self):
        return self.code

    def getCity(self):
        return self.city

    def getCountry(self):
        return self.country

    # Setter functions
    def setCity(self, city):
        self.city = city

    def setCountry(self, country):
        self.country = country
