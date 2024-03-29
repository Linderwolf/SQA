# AvailableGamesManager.py
#
# Contains the Game and AvailableGamesFileManager classes.
#
# Processes any Object or File/IO required of AvailableGames
# 
# Authors: Matthew, Ajaane, Peter, Russell
import re
import os

class Game:
    """
    This class is designed to represent the games in the system.

    ...

    Attributes
    ----------
    name : str
        the username of the game
    price : float
        the price of the game
    seller : str
        the username of the seller of the game

    """
    
    # A constructor creating a new Game object with the specified values
    def __init__(self, name, seller, price):
        self.name = name
        self.price = price
        self.seller = seller


class AvailableGamesFileManager:
    """
    The AvailableGamesFileManager class is responsible for managing game-related operations 
    and for file management for the AvailableGames.txt file
    
    ...

    Attributes
    ----------
    availableGames : List[Game]
        a list of Game objects

    Methods
    -------
    getPriceByName(gameName)
        An accessor method that returns the price with the specified game name
        
    getUsersGames(username)
        Returns a list of all the games being sold by the given user
        
    readAvailableGames(filename)
        Reads game data from AvailableGames.txt and populates the availableGames 
        list with Game objects created from the data

    
    writeToFile(filename)
        Writes game data from the availableGames list to the specified file. 
        Each game’s data is formatted and written as a separate line in the file

        
   addGame(gameName, sellerName, price)
        Creates new Game object with specified Game data and adds it to the availableGames list
        
    removeGame(gameName)
        Removes the Game with the specified gameName from the availableGames list
        
    parseGameLine(line)
        Parses a line from the AvailableGames.txt, extracting information such as the game name, 
        owner, and price

    """
    
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
        print(f"Game {newGame.name} added successfully.")

    # Updates the availableGames attribute to not include the given game
    def removeGame(self, gameName):
        self.availableGames = [game for game in self.availableGames if game.name != gameName]

    # Reads user data from CurrentUserAccounts.txt and populates the availableGames list with Game objects created from the data
    def readAvailableGames(self, filename):
        if not os.path.exists(filename):
            raise IOError("ERROR: Fatal Error - File '{filename}' not found.")
            return
        with open(filename, 'r') as file:
            for line in file:
                result = self.parseGameLine(line)
                if result is not None:
                    name, owner, price = result
                    self.availableGames.append(Game(name, owner, float(price)))
                    
        file.close()
        
    # Writes game data from the availableGames list to the specified file.
    def writeToFile(self, filename):
        if not os.path.exists(filename):
            raise IOError("ERROR: Fatal Error - File '{filename}' not found.")
            return
        with open(filename, 'w') as file:
            for game in self.availableGames:
                line = f"{game.name:<26} {game.seller:<15} {game.price:06.2f}\n"
                file.write(line)
            file.write("END")
        file.close()

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
            raise Exception(f"ERROR: Fatal Error - Invalid line format: {line} in AvailableGames.txt")
        
        return gameName, owner, price
