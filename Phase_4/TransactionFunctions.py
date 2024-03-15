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
    def __init__(self, userManager, gameManager):
        self.userManager = userManager
        self.gameManager = gameManager
        
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
        
    def logout(self, transaction):
        return

    def create(self, transaction):
        newUser, userType, credit = parseMost(transaction)
        self.userManager.addUser(newUser, userType, credit)
        self.userManager.writeToFile(userAccountsFilePath)

    def delete(self, transaction):
        transactionCode, user, userType, credit = parseMost(transaction)
    
        self.userManager.readFromFile(userAccountsFilePath)
        self.userManager.removeUser(user)
        self.userManager.writeToFile()
        

        self.gameManager.readAvailableGames(availableGameFilePath)
        usersGames = self.gameManager.getUsersGames(user)
        for game in usersGames:
            self.gameManager.removeGame(game)


    def sell(self, transaction):
        transactionCode, gameName, seller, gamePrice = parseSell(transaction)
        self.gameManager.addGame()
        self.gameManager.writeToFile(availableGameFilePath)

    def buy(self, transaction):
        transactionCode, gameName, seller, buyer, gamePrice = parseBuy(transaction)
        # Update buyer and seller credits
        self.userManager.updateUsercredit(buyer, float(gamePrice) * -1)
        self.userManager.updateUsercredit(seller, float(gamePrice))
        self.userManager.writeToFile(userAccountsFilePath)
        # Add game to Game Collection
        appendToGameCollection(gameName, seller)

    def refund(self, transaction):
        transactionCode, gameName, buyer, seller, refundCredit = parseRefund(transaction)
        # Update buyer and seller credits
        self.userManager.updateUsercredit(buyer, refundCredit)
        self.userManager.updateUsercredit(seller, float(refundCredit)*-1)
        self.userManager.writeToFile(userAccountsFilePath)       
        # Remove game from buyer's game collection
        lineToRemove = f"{gameName:<26} {buyer:<15}\n"
        removeGameFromCollection(lineToRemove)   

    def addCredit(self, transaction):
        transactionCode, user, userType, credit = parseMost(transaction)
        self.userManager.readFromFile(userAccountsFilePath)
        
        self.userManager.updateUserBalance(user, credit)
        self.userManager.writeToFile(userAccountsFilePath)
        
        