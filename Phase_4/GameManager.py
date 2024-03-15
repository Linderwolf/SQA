import re

class Game:
    def __init__(self, name, seller, price):
        self.name = name
        self.price = price
        self.seller = seller


class AvailableGamesFileManager:
    def __init__(self):
        self.availableGames = []
        
    def getPriceByName(self, gameName):
        for game in self.availableGames:
            if game.name == gameName:
                return game.price
        return None  # Return None if the game name is not found
    
    def getUsersGames(self, username):
        return [game.name for game in self.availableGames if game.seller == username]

    def addGame(self, gameName, sellerName, price):
        newGame = Game(gameName, sellerName, price)
        self.availableGames.append(newGame)
        print(f"Game {newGame} added successfully.")
        
    def removeGame(self, gameName):
        self.availableGames = [game for game in self.availableGames if game.name != gameName]
        
    def readAvailableGames(self, filename):
        with open(filename, 'r') as file:
            for line in file:
                result = self.parseGameLine(line)
                if result is not None:
                    name, owner, price = result
                    self.availableGames.append(Game(name, owner, float(price)))

    def writeToFile(self, filename):
        with open(filename, 'w') as file:
            for game in self.availableGames:
                line = f"{game.name:<20} {game.owner:<15} {game.price:0.2f}\n"
                file.write(line)

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