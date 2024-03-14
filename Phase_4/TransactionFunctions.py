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
    gameManager.write_to_file(gameManager,availableGameFilePath)
    return  
def buy(transaction):
    # Read user data from the CurrentUserAccounts.txt and store it as a list of User objects in userManager
    userManager = UserManager.UserFileManager()
    userManager.readFromFile(userAccountsFilePath)
    # Read existing games from the AvailableGames.txt file and store it as a list of Game objects in availableGamesManager
    availableGamesManager = GameManager.AvailableGamesFileManager()
    availableGamesManager.readAvailableGames(availableGameFilePath)
    
    transactionCode, gameName, seller, buyer, gamePrice = parseBuy(transaction)

    # Create User objects for seller and buyer
    sellerUser = userManager.getUserByUsername(seller)
    buyerUser = userManager.getUserByUsername(buyer)
    
    # Get game price
    gamePrice = availableGamesManager.getPriceByName(gameName)
    
    # Update credits for seller and buyer
    sellerUser.credit += gamePrice
    buyerUser.credit -= gamePrice
    
    #print(f'buyerUser.credit: {buyerUser.credit}  sellerUser.credit: {sellerUser.credit}')
    
    # Write updated user info to CurrentUserAccounts.txt
    userManager.writeToFile(userAccountsFilePath)
    # Write to GameCollection.txt 
    appendToGameCollection(gameName, seller)
    return  
def refund(transaction):
    transactionCode, gameName, buyer, seller, refundCredit = parseRefund(transaction)
    
    # Get instances of UserFileManager
    userManager = UserManager.UserFileManager()
    userManager.readFromFile(userAccountsFilePath)
    
    # Retrieve user objects for buyer and seller
    buyerUser = userManager.getUserByUsername(buyer)
    sellerUser = userManager.getUserByUsername(seller)

    # Check if both buyer and seller exist
    if buyerUser is not None and sellerUser is not None:
        # Calculate the updated balances
        newBuyerBalance = buyerUser.credit + float(refundCredit)
        newSellerBalance = sellerUser.credit - float(refundCredit)

        # Update user balances
        userManager.updateUsercredit(buyer, newBuyerBalance)
        userManager.updateUsercredit(seller, newSellerBalance)
        
        # Write updated user info to CurrentUserAccounts.txt
        userManager.writeToFile(userAccountsFilePath)
        #print(f"Refund successful. Buyer: {buyer}, Seller: {seller}, Refund Credit: {refundCredit}")
        
        # Remove game from buyer's game collection
        lineToRemove = f"{gameName:<26} {buyer:<15}\n"
        removeGameFromCollection(lineToRemove)
        
    else:
        print(f"Error: Buyer ({buyer}) or Seller ({seller}) not found.")
    return   
def addCredit(transaction):
    user, userType, credit = parseMost(transaction)
    userManager = UserManager(user, "", userType, credit, "")
    userManager.updateUserBalance()