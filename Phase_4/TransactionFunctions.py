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

# <summary>
# Functions for executing each transaction in the DailyTransaction file
# </summary>
# <param name="transactions">A reference to the vector of transactions performed by the User</param>
# <param name="currentUser">A reference to the User object representing logged in User</param>
class TransactionManager:
    def __init__(self, userManager, gameManager):
        self.userManager = userManager
        self.gameManager = gameManager
        
    # <summary>
    # Sends transaction to appropriate function for backend processing
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
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
        
    # <summary>
    # Empty transaction for the "logout" command
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
    def logout(self, transaction):
        return

    # <summary>
    # Creates a new user and adds the user to the CurrentUserAccounts.txt file
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
    def create(self, transaction):
        newUser, userType, credit = parseMost(transaction)
        self.userManager.addUser(newUser, userType, credit)
        self.userManager.writeToFile(userAccountsFilePath)

    # <summary>
    # Deletes a user from the CurrentUserAccounts.txt file
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
    def delete(self, transaction):
        user, userType, credit = parseMost(transaction)
        self.userManager.removeUser(user)
        self.userManager.writeToFile(userAccountsFilePath)

        usersGames = self.gameManager.getUsersGames(user)
        for game in usersGames:
            print(f"Removing {game} from {user}")
            self.gameManager.removeGame(game)
        self.gameManager.writeToFile(availableGameFilePath)

    # <summary>
    # Creates a new game to sell and adds the game to the AvailableGames.txt file
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
    def sell(self, transaction):
        transactionCode, gameName, seller, gamePrice = parseSell(transaction)
        self.gameManager.addGame()
        self.gameManager.writeToFile(availableGameFilePath)

    # <summary>
    # Adds a game to a user's collection, adds to the seller's credit and deducts from the buyer's credit based on the game's price
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
    def buy(self, transaction):
        transactionCode, gameName, seller, buyer, gamePrice = parseBuy(transaction)
        # Update buyer and seller credits
        self.userManager.updateUsercredit(buyer, float(gamePrice) * -1)
        self.userManager.updateUsercredit(seller, float(gamePrice))
        self.userManager.writeToFile(userAccountsFilePath)
        # Add game to Game Collection
        appendToGameCollection(gameName, seller)

    # <summary>
    # Removes a game from the user's collection, adds to the buyer's credit and deducts from the seller's credit based on the game's price
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
    def refund(self, transaction):
        transactionCode, gameName, buyer, seller, refundCredit = parseRefund(transaction)
        # Update buyer and seller credits
        self.userManager.updateUsercredit(buyer, refundCredit)
        self.userManager.updateUsercredit(seller, float(refundCredit)*-1)
        self.userManager.writeToFile(userAccountsFilePath)       
        # Remove game from buyer's game collection
        lineToRemove = f"{gameName:<26} {buyer:<15}\n"
        removeGameFromCollection(lineToRemove)   

    # <summary>
    # Increases the amount of credit a user has
    # </summary>
    # <param name="transactions">A transaction as a string from the DailyTransaction file</param>
    def addCredit(self, transaction):
        user, userType, credit = parseMost(transaction)
        self.userManager.updateUsercredit(user, float(credit))
        self.userManager.writeToFile(userAccountsFilePath)
        
        