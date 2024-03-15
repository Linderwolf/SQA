# SQA Phase 4
# Matthew, Ajaane, Peter, Russell


# Helper Functions
from HelperFunctions import parseMost
from HelperFunctions import parseRefund
from HelperFunctions import parseSell
from HelperFunctions import parseBuy
from HelperFunctions import appendToGameCollection
from HelperFunctions import removeGameFromCollection
from HelperFunctions import getTransactionCode

# Specify the file path for CurrentUserAccounts.txt
userAccountsFilePath = "CurrentUserAccounts.txt"
# Specify the file path for AvailableGames.txt
availableGameFilePath = "AvailableGames.txt"

class TransactionManager:
    # A constructor creating a new TransactionManager object with the specified values
    def __init__(self, userManager, gameManager):
        self.userManager = userManager
        self.gameManager = gameManager

    # Gets the transaction code indicating which type of transaction the line represents and calls the appropriate transaction function
    def processTransaction(self, transaction):
        transactionCode = getTransactionCode(transaction)
        match transactionCode:
            case "00": self.logout(transaction)
            case "01": self.create(transaction) # Russell
            case "02": self.delete(transaction) # Matthew
            case "03": self.sell(transaction) # Peter
            case "04": self.buy(transaction) # Ajaane
            case "05": self.refund(transaction) # Ajaane
            case "06": self.addCredit(transaction) # Matthew

    # Does nothing because the logout transaction does not edit any of the files
    def logout(self, transaction):
        return

    # Creates a new User object, appends it to the userManager List, and writes it to the UserAccounts file
    def create(self, transaction):
        newUser, userType, credit = parseMost(transaction)
        self.userManager.addUser(newUser, userType, credit)
        self.userManager.writeToFile(userAccountsFilePath)

    # Deletes all references of a User from the userAccounts and availableGames files
    def delete(self, transaction):
        user, userType, credit = parseMost(transaction)
        self.userManager.removeUser(user)
        self.userManager.writeToFile(userAccountsFilePath)

        usersGames = self.gameManager.getUsersGames(user)
        for game in usersGames:
            print(f"Removing {game} from {user}")
            self.gameManager.removeGame(game)
        self.gameManager.writeToFile(availableGameFilePath)

    # Creates a new Game object and writes it to the availableGames file
    def sell(self, transaction):
        transactionCode, gameName, seller, gamePrice = parseSell(transaction)
        self.gameManager.addGame()
        self.gameManager.writeToFile(availableGameFilePath)

    # Adds a game to a buying User’s collection in the gameCollection file, Credits a seller, and deducts that amount from the buyer
    def buy(self, transaction):
        transactionCode, gameName, seller, buyer, gamePrice = parseBuy(transaction)
        # Update buyer and seller credits
        self.userManager.updateUsercredit(buyer, float(gamePrice) * -1)
        self.userManager.updateUsercredit(seller, float(gamePrice))
        self.userManager.writeToFile(userAccountsFilePath)
        # Add game to Game Collection
        appendToGameCollection(gameName, seller)

    # Removes an owned game from a User’s collection in the gameCollection file, credits that buyer, and deducts that amount from the seller
    def refund(self, transaction):
        transactionCode, gameName, buyer, seller, refundCredit = parseRefund(transaction)
        # Update buyer and seller credits
        self.userManager.updateUsercredit(buyer, refundCredit)
        self.userManager.updateUsercredit(seller, float(refundCredit)*-1)
        self.userManager.writeToFile(userAccountsFilePath)       
        # Remove game from buyer's game collection
        lineToRemove = f"{gameName:<26} {buyer:<15}\n"
        removeGameFromCollection(lineToRemove)   

    # Adds the given credit to the user’s balance and updates the CurrentUserAccounts file to reflect this change
    def addCredit(self, transaction):
        user, userType, credit = parseMost(transaction)
        self.userManager.updateUsercredit(user, float(credit))
        self.userManager.writeToFile(userAccountsFilePath)
        
        
