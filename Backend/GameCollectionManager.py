# GameCollectionManager.py
#
# Contains the CollectionEntry and GameCollectionManager classes.
#
# Processes any Object or File/IO required of GameCollection
# 
# Authors: Matthew, Ajaane, Peter, Russell
import re
import os

class CollectionEntry:
    """
    This class is designed to represent the entries in the GameCollection.txt file.

    ...

    Attributes
    ----------
    gameName : str
        the name of the game owned
    owner : str
        the username of the owner of the game

    """
    
    # A constructor creating a new CollectionEntry object with the specified values
    def __init__(self, gameName, owner):
        self.gameName = gameName
        self.owner = owner

class GameCollectionManager:
    """
    The GameCollectionManager class is responsible for managing game-related operations 
    and for file management for the GameCollection.txt file
    
    ...

    Attributes
    ----------
    collection : List[CollectionEntry]
        a list of CollectionEntry objects

    Methods
    -------

    addEntry(gameName, owner)
        Creates new CollectionEntry object with specified game name and owner username
        adds it to the collection list
        
    removeEntry(gameName, owner)
        Removes the CollectionEntry with the specified game name and owner from the collection list
        
    readCollection(filename)
        Reads the data from GameCollection.txt and populates the collection 
        list with CollectionEntry objects

    
    writeToCollection(filename)
        Writes collection data from the collection list to the specified file. 

    parseLine(line)
        Parses a line from the GameCollection.txt, extracting information such as the game name, and 
        owner

    """
    # A default constructor to create a new GameCollectionManager object with the default attribute, an empty list of CollectionEntry objects
    def __init__(self):
        self.collection = []
        
    # Creates new CollectionEntry object with the specified data and adds it to the collection list
    def addEntry(self, gameName, owner):
        newEntry = CollectionEntry(gameName, owner)
        self.collection.append(newEntry)
        
    # Removes the entry with specified data from the collection list
    def removeEntry(self, gameName, owner):
        for entry in self.collection:
            if entry.gameName == gameName and entry.owner == owner:
                self.collection.remove(entry)
                return
        print(f"Entry: {gameName} {owner} not found.")
            
    # Reads the GameCollection.txt file and populates the collection list
    def readCollection(self, filename):
        if not os.path.exists(filename):
            raise IOError("ERROR: Fatal Error - File '{filename}' not found.")
            return
        with open(filename, 'r') as file:
            for line in file:
                result = self.parseLine(line)
                if result is not None:
                    gameName, owner = result
                    self.collection.append(CollectionEntry(gameName, owner))
                    
        file.close()
    
    # Writes the data from the collection list to the specified file              
    def writeToCollection(self, filename):
        if not os.path.exists(filename):
            raise IOError("ERROR: Fatal Error - File '{filename}' not found.")
            return
        with open(filename, 'w') as file:
            for entry in self.collection:
                line = f"{entry.gameName:<26} {entry.owner:<15}\n"
                file.write(line)
            file.write("END")
            
        file.close()
                
                    
    # Parses a line from the GameCollection.txt, extracting information such as the game name, owner, and price
    def parseLine(self, line):
        pattern = re.compile(r'^(.{26})\s{1,15}(.{15})\s{1,}$')
        match = pattern.match(line)
        if (line == "END"):
            return None
        if match:
            gameName = match.group(1).strip()
            owner = match.group(2).strip()
        else:
            raise Exception(f"ERROR: Fatal Error - Invalid line format: {line} in GameCollection.txt")
        
        return gameName, owner
    