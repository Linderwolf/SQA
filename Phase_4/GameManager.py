import re

class Game:
    # A constructor creating a new Game object with the specified values
    def __init__(self, name, seller, price):
        self.name = name
        self.price = price
        self.seller = seller


class AvailableGamesFileManager:
    # A default constructor to create a new AvailableGamesFileManager object with the default attribute, an empty list of Game objects
    def __init__(self):
        self.availableGames = []

    # An accessor method that returns the price with the specified game name
    def getPriceByName(self, gameName):
        for game in self.availableGames:
            if game.name == gameName:
                return game.price
        return None  # Return None if the game name is not found

    # Returns a list of all the games being sold by the given user
    def getUsersGames(self, username):
        return [game.name for game in self.availableGames if game.seller == username]

    # Creates new Game object with specified Game data and adds it to the availableGames list
    def addGame(self, gameName, sellerName, price):
        newGame = Game(gameName, sellerName, price)
        self.availableGames.append(newGame)
        print(f"Game {newGame} added successfully.")

    # Updates the availableGames attribute to not include the given game
    def removeGame(self, gameName):
        self.availableGames = [game for game in self.availableGames if game.name != gameName]

    # Reads user data from CurrentUserAccounts.txt and populates the availableGames list with Game objects created from the data
    def readAvailableGames(self, filename):
        with open(filename, 'r') as file:
            for line in file:
                result = self.parseGameLine(line)
                if result is not None:
                    name, owner, price = result
                    self.availableGames.append(Game(name, owner, float(price)))
    # Writes game data from the availableGames list to the specified file.
    # Each game’s data is formatted and written as a separate line in the file
    def writeToFile(self, filename):
        with open(filename, 'w') as file:
            for game in self.availableGames:
                line = f"{game.name:<26} {game.seller:<15} {game.price:06.2f}\n"
                file.write(line)

    # Parses a line from the AvailableGames.txt, extracting information such as the game name, owner, and price
    def parseGameLine(self, line):
        pattern = re.compile(r'^(.{26})\s{1,15}(.{15})\s{1,}(\d+\.\d{2})$')
        match = pattern.match(line)
        if (line == "END"):
            return None
        if match:
            gameName = match.group(1).strip()
            owner = match.group(2).strip()
            price = float(match.group(3))
        else:
            print(f"Invalid format: {line}")
            return None
        
        return gameName, owner, price
