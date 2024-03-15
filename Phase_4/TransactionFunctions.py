# SQA Phase 4
# Matthew, Ajaane, Peter, Russell

# Classes

import UserManager
import GameManager
import CollectionManager

# Helper Functions

from HelperFunctions import parseMost
from HelperFunctions import parseRefund
from HelperFunctions import parseSell
from HelperFunctions import parseBuy
from HelperFunctions import appendToGameCollection
from HelperFunctions import removeGameFromCollection

# Specify the file path for CurrentUserAccounts.txt
userAccountsFilePath = "CurrentUserAccounts.txt"
# Specify the file path for AvailableGames.txt
availableGameFilePath = "AvailableGames.txt"

def logout(transaction):
    return
def create(transaction):
    userManager = UserManager.UserFileManager()
    newUser, userType, credit = parseMost(transaction)
    userManager.addUser(userManager,newUser,userType,credit)
    userManager.writeToFile(userManager,userAccountsFilePath)
    return  
def delete(transaction):
    user, userType, credit = parseMost(transaction)
    return  
def sell(transaction):
    gameManager = GameManager.AvailableGamesFileManager()
    transactionCode, gameName, seller, gamePrice = parseSell(transaction)
    gameManager.addGame()
    gameManager.writeToFile(gameManager,availableGameFilePath)
    return  
def buy(transaction):
    # Get instances of UserFileManager
    userManager = UserManager.UserFileManager()
    userManager.readFromFile(userAccountsFilePath)
    
    transactionCode, gameName, seller, buyer, gamePrice = parseBuy(transaction)
    
    # Update buyer and seller credits
    userManager.updateUsercredit(buyer, float(gamePrice)*-1)
    userManager.updateUsercredit(seller, float(gamePrice))
    userManager.writeToFile(userAccountsFilePath)
    
    # Add game to Game Collection
    appendToGameCollection(gameName, seller)
    return  
def refund(transaction):
    # Get instances of UserFileManager
    userManager = UserManager.UserFileManager()
    userManager.readFromFile(userAccountsFilePath)
    
    transactionCode, gameName, buyer, seller, refundCredit = parseRefund(transaction)
    
    # Update buyer and seller credits
    userManager.updateUsercredit(buyer, refundCredit)
    userManager.updateUsercredit(seller, float(refundCredit)*-1)
    userManager.writeToFile(userAccountsFilePath)
    
    # Remove game from buyer's game collection
    lineToRemove = f"{gameName:<26} {buyer:<15}\n"
    removeGameFromCollection(lineToRemove)   
    return   
def addCredit(transaction):
    user, userType, credit = parseMost(transaction)
    userManager = UserManager(user, "", userType, credit, "")
    userManager.updateUserBalance()