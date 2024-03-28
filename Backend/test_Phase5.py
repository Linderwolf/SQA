# testing.py
#
# The Test file. Similar to main file. Sets up file variables, and reads transactions from DailyTransactions files for processing 
# 
# Authors: Matthew, Ajaane, Peter, Russell


# https://stackoverflow.com/questions/42512016/how-to-compare-two-files-as-part-of-unittest-while-getting-useful-output-in-cas


# Classes
from UserManager import UserFileManager
from AvailableGamesManager import AvailableGamesFileManager
from GameCollectionManager import GameCollectionManager
from TransactionFunctions import TransactionManager
import HelperFunctions as hf

# Specify the file paths for CurrentUserAccounts.txt, AvailableGames.txt, and DailyTransactions.txt
userAccountsFilePath = "CurrentUserAccounts.txt"
availableGameFilePath = "AvailableGames.txt"
gameCollectionFilePath = "GameCollection.txt"
dailyTransactionFilePath = "DailyTransactions.txt"

import os.path
import pytest



# NOTE Need to make function that refreshes the data in the .txt files
# this function can be made per manager (e.g. userfile, gamefile, collectionfile)
# or can be all in the same function
def refreshData():
    return

# Testing starts

# Test UserFileManager Class
#
# Create instances of FileManager object
userFileManager = UserFileManager()
# Read user data from the file
userFileManager.readFromFile(userAccountsFilePath)
# 
# test getUserByUsername(username)
def test_getUserByUsername():
    user = userFileManager.getUserByUsername("admin")
    assert user.username == 'admin'
    assert user.userType == 'AA'
    assert user.credit == 100.00
# test readFromFile(filename)
def test_readFromFile():
    userFile = os.path.isfile(userAccountsFilePath)
    assert userFile
# test addUser(username, userType, credit)
def test_addUser():
    userFileManager.addUser('George','BS',13.25)
    assert userFileManager.getUserByUsername('George')
# test writeToFile(filename)
def test_writeToFile():
    # userFileManager.addUser('George','BS',13.25)
    userFileManager.writeToFile(userAccountsFilePath)
    with open(userAccountsFilePath, 'r') as file:
        for i, line in enumerate(file):
            if i == 4:
                parts = line.split()
                username,userType,credit = parts
                assert username == "George"
                assert userType == "BS"
                assert credit == "000013.25"
# test removeUser(username)
def test_removeUser():
    userFileManager.removeUser('George')
    userFileManager.writeToFile(userAccountsFilePath)
    with open(userAccountsFilePath, 'r') as file:
        for i, line in enumerate(file):
            if i == 4:
                assert line == "END"
    # with open(userAccountsFilePath, 'r') as file:
    #     assert "George          BS 000013.25" not in 
# test updateUsercredit
def test_updateUsercredit():
    # increase credit
    userFileManager.updateUsercredit("fullstandard",100)
    userFileManager.writeToFile(userAccountsFilePath)
    user = userFileManager.getUserByUsername("fullstandard")
    assert user.username == "fullstandard"
    assert user.credit == 200.00
    # decrease credit
    userFileManager.updateUsercredit("fullstandard",-100)
    userFileManager.writeToFile(userAccountsFilePath)
    user = userFileManager.getUserByUsername("fullstandard")
    assert user.username == "fullstandard"
    assert user.credit == 100.00
# Test AvailableGamesFileManager Class
#
# Create instances of FileManager object
gameFileManager = AvailableGamesFileManager()
# Read available games data from the file
gameFileManager.readAvailableGames(availableGameFilePath)
#
# test getPriceByName(gameName)
# test getUsersGames(username)
# test readAvailableGames(filename)
# test writeToFile(filename)
# test addGame(gameName, sellerName, price)
# test removeGame(gameName)
# test parseGameLine(line)

# Test GameCollectionManager Class
#
# Create instances of FileManager object
gameCollectionManager = GameCollectionManager()
# Read game collection data from the file
gameCollectionManager.readCollection(gameCollectionFilePath)
#
# test addEntry(gameName, owner)
# test removeEntry(gameName, owner)
# test readCollection(filename)
# test writeToCollection(filename)
# test parseLine(line)


# Test TransacitonManager Class
#
# Create instance of and TransactionManager object
transactionManager = TransactionManager(userFileManager, gameFileManager, gameCollectionManager)
#
# test transaction.logout(self, transaction)
#def test_logout():
    
# test transaction.create(self, transaction)
def test_create(capfd):
    # emptyTransaction
    with pytest.raises(ValueError) as e_info:
        hf.parseMost("")
        
    # validTransaction   
    try:  
        hf.parseMost("01 JDoe            FS 000000.00")
    except Exception as excinfo:  
        pytest.fail(f"Unexpected exception raised: {excinfo}")
    
    # invalidUserInfo
    message = userFileManager.addUser("user1", "AA", -10000.00)
    assert message == "ERROR: Violation of Constraint: Credit cannot be less than 0."
    
    refreshData()  
    
    # validAdd
    userFileManager.addUser("newUser", "AA", 100)
    assert userFileManager.users[-1].username == "newUser"
    
    # validWrite
    try:  
        userFileManager.writeToFile(userAccountsFilePath)
    except Exception as excinfo:  
        pytest.fail(f"Unexpected exception raised: {excinfo}")
        
    file = open(userAccountsFilePath) 
    content = file.readlines() 
    assert content[-2] == "newUser         AA 000100.00\n"
    
    refreshData()
    
    # invalidFilepath
    with pytest.raises(Exception) as e_info:
        userFileManager.writeToFile("wrongPath")

    refreshData()
    

# test transaction.delete(self, transaction)
def test_delete():
    # emptyTransaction
    with pytest.raises(ValueError) as e_info:
        hf.parseMost("")
        
    # validTransaction   
    try:  
        hf.parseMost("02 JohnDoe         BS 000010.00")
    except Exception as excinfo:  
        pytest.fail(f"Unexpected exception raised: {excinfo}")
        
    # nonexistentUser
    emptyUserManager = UserFileManager()
    emptyUserManager.removeUser("jane")
    assert len(emptyUserManager.users) == 0
    
    # validUser
    usernameToCheck = "JohnDoe"
    userManager = UserFileManager()
    userManager.readFromFile(userAccountsFilePath)
    userManager.removeUser(usernameToCheck)    
    userFound = False
    for user in userManager.users:
        if user.username == usernameToCheck:
            userFound = True
            break
    assert userFound == False
    
    
    # invalidAccountsFilepath
    with pytest.raises(Exception) as e_info:
        userFileManager.writeToFile("wrongPath")

    # notSelling
    lengthOfAvailableGames = len(gameFileManager.availableGames)
    gameFileManager.getUsersGames("buystandard")
    assert lengthOfAvailableGames == len(gameFileManager.availableGames)
    
    # validWrite
    try:  
        userManager.writeToFile(userAccountsFilePath)
    except Exception as excinfo:  
        pytest.fail(f"Unexpected exception raised: {excinfo}")
        
    refreshData()
    
    # selling
    gameManager = AvailableGamesFileManager()
    usersGames = gameManager.getUsersGames("sellstandard")
    for game in usersGames:
            print(f"Removing {game} from {user}")
            gameManager.removeGame(game)
    
    #validGameWrite
    gameManager.writeToFile(availableGameFilePath)
    sellstandardRemoved = True  

    with open(availableGameFilePath, 'r') as file:
        lines = file.readlines()  

    for line in lines:
        columns = line.split()
        if len(columns) >= 2 and columns[1] == "sellstandard":
            sellstandardRemoved = False
            break
    
    assert sellstandardRemoved == True
        
    # invalidAvailableGamesFilepath
    with pytest.raises(Exception) as e_info:
        gameFileManager.writeToFile("wrongPath")
        
    refreshData()
        
# test transaction.sell(self, transaction)
def test_sell():
    # emptyTransaction
    with pytest.raises(ValueError) as e_info:
        hf.parseSell("")
    
    # validAdd
    name = "testGame"
    seller = "sellstandard"
    price = 20.00
    gameManager = AvailableGamesFileManager()
    gameManager.addGame(name, seller, price)
    assert gameManager.availableGames[-1].name == name
    assert gameManager.availableGames[-1].seller == seller
    assert gameManager.availableGames[-1].price == price
    
    #validWrite    
    try:  
        gameManager.writeToFile(availableGameFilePath)
    except:  
        pytest.fail(f"Cannot write to {availableGameFilePath}")
        
    file = open(availableGameFilePath) 
    content = file.readlines() 
    assert content[-2] == "testGame                   sellstandard    020.00\n"
    
    
    refreshData()
        
    # invalidAvailableGamesFilepath
    with pytest.raises(Exception) as e_info:
        gameFileManager.writeToFile("wrongPath")

    
# test transaction.buy(self, transaction)
def test_buy(capfd):
    # emptyTransaction
    with pytest.raises(ValueError) as e_info:
        hf.parseBuy("")
        
    # nonexistentBuyerUser
    userFileManager = UserFileManager()
    userFileManager.readFromFile(userAccountsFilePath)
    usersBefore = userFileManager.users
    userFileManager.updateUsercredit("buyer", 100)
    usersAfter = userFileManager.users
    assert usersBefore == usersAfter
    
    captured = capfd.readouterr()
    print("Captured stderr: |", captured.out, '|')
    assert "User buyer not found." in captured.out
    
    # nonexistentSellerUser
    usersBefore = userFileManager.users
    userFileManager.updateUsercredit("seller", 100)
    usersAfter = userFileManager.users
    assert usersBefore == usersAfter
    
    #existent user 
    existingUser = "buystandard"
    user = userFileManager.getUserByUsername(existingUser)
    predictedBalance = user.credit + 10.00
    userFileManager.updateUsercredit(existingUser, 10.00)
    assert predictedBalance == user.credit
    
    # validWrite
    try:  
        userFileManager.writeToFile(userAccountsFilePath)
    except:  
        pytest.fail(f"Cannot write to {userAccountsFilePath}")
        
    with open(userAccountsFilePath, 'r') as file:
        lines = file.readlines()  

    balanceMatch = False
    for line in lines:
        columns = line.split()
        if columns[0] == existingUser and float(columns[2]) == predictedBalance:
            balanceMatch = True
            break
    assert balanceMatch == True
    
    refreshData()
    
    # buyerNegativeCredit
    userBefore = userFileManager.getUserByUsername(existingUser)
    userFileManager.updateUsercredit(existingUser, -1000)
    userAfter = userFileManager.getUserByUsername(existingUser)
    assert userBefore.credit == userAfter.credit
    
    
    # invalidAccountsFilepath
    with pytest.raises(Exception) as e_info:
        userFileManager.writeToFile("wrongPath")
        
    # validAddEntry
    collectionManager = GameCollectionManager()
    collectionManager.readCollection(gameCollectionFilePath)
    collectionManager.addEntry("testGame", "testOwner")
    assert collectionManager.collection[-1].gameName == "testGame"
    assert collectionManager.collection[-1].owner == "testOwner"
    
    # validCollectionWrite
    try:  
        collectionManager.writeToCollection(gameCollectionFilePath)
    except:  
        pytest.fail(f"Cannot write to {gameCollectionFilePath}")
        
    file = open(gameCollectionFilePath) 
    content = file.readlines() 
    assert content[-2] == "testGame                   testOwner      \n"
    
    refreshData()
        
    # invalidAvailableGamesFilepath
    with pytest.raises(Exception) as e_info:
        gameFileManager.writeToFile("wrongPath")
    
    
# test transaction.refund(self, transaction)
def test_refund(capfd):
    # emptyTransaction
    with pytest.raises(ValueError) as e_info:
        hf.parseRefund("")
        
    # nonexistentBuyerUser
    userFileManager = UserFileManager()
    userFileManager.readFromFile(userAccountsFilePath)
    usersBefore = userFileManager.users
    userFileManager.updateUsercredit("buyer", 100)
    usersAfter = userFileManager.users
    assert usersBefore == usersAfter
    
    captured = capfd.readouterr()
    print("Captured stderr: |", captured.out, '|')
    assert "User buyer not found." in captured.out
    
    
    # nonexistentSellerUser
    usersBefore = userFileManager.users
    userFileManager.updateUsercredit("seller", 100)
    usersAfter = userFileManager.users
    assert usersBefore == usersAfter
    
    #existent user 
    existingUser = "sellstandard"
    user = userFileManager.getUserByUsername(existingUser)
    predictedBalance = user.credit - 10.00
    userFileManager.updateUsercredit(existingUser, -10.00)
    assert predictedBalance == user.credit
    
    # validWrite
    try:  
        userFileManager.writeToFile(userAccountsFilePath)
    except:  
        pytest.fail(f"Cannot write to {userAccountsFilePath}")
        
    with open(userAccountsFilePath, 'r') as file:
        lines = file.readlines()

    balanceMatch = False
    for line in lines:
        columns = line.split()
        if columns[0] == existingUser and float(columns[2]) == predictedBalance:
            balanceMatch = True
            break
    assert balanceMatch == True
    
    refreshData()
    
    
    # sellerNegativeCredit
    userBefore = userFileManager.getUserByUsername(existingUser)
    print(f"before: {userBefore.credit}")
    userFileManager.updateUsercredit(existingUser, -10000)
    userAfter = userFileManager.getUserByUsername(existingUser)
    print(f"after: {userAfter.credit}")
    assert userBefore.credit == userAfter.credit
    
    # validRemoveEntry
    collectionManager = GameCollectionManager()
    collectionManager.readCollection(gameCollectionFilePath)
    collectionManager.removeEntry("testGame", "testOwner")
    gameFound = False
    for entry in collectionManager.collection:
        if entry.gameName == "testGame":
            gameFound = True
            print(entry.gameName)
            break
    assert gameFound == False
    
    # validCollectionWrite
    try:  
        collectionManager.writeToCollection(gameCollectionFilePath)
    except:  
        pytest.fail(f"Cannot write to {gameCollectionFilePath}")
        
    gameRemoved = True 

    with open(gameCollectionFilePath, 'r') as file:
        lines = file.readlines()  

    for line in lines:
        columns = line.split()
        if len(columns) >= 2 and columns[1] == "testGame":
            gameRemoved = False
            break
    
    assert gameRemoved == True
    
    refreshData()  
    
    # invalidAccountsFilepath
    with pytest.raises(Exception) as e_info:
        userFileManager.writeToFile("wrongPath")
    
    # invalidCollectionFilepath
    with pytest.raises(Exception) as e_info:
        gameCollectionManager.writeToCollection("wrongPath")
    
    
# test transaction.addCredit(self, transaction)
def test_addCredit(capfd):
    # emptyTransaction
    with pytest.raises(ValueError) as e_info:
        hf.parseMost("")
        
    # nonexistentUser
    userFileManager.updateUsercredit("nonexistentUser", 20.00)
    captured = capfd.readouterr()
    print("Captured stderr: |", captured.out, '|')
    assert "User nonexistentUser not found." in captured.out
    
    #validUpdateUserBalance
    existingUser = "buystandard"
    user = userFileManager.getUserByUsername(existingUser)
    predictedBalance = user.credit + 10.00
    userFileManager.updateUsercredit(existingUser, 10.00)
    assert predictedBalance == user.credit
    
    # validWrite
    try:  
        userFileManager.writeToFile(userAccountsFilePath)
    except:  
        pytest.fail(f"Cannot write to {userAccountsFilePath}")
        
    with open(userAccountsFilePath, 'r') as file:
        lines = file.readlines()  

    balanceMatch = False
    for line in lines:
        columns = line.split()
        if columns[0] == existingUser and float(columns[2]) == predictedBalance:
            balanceMatch = True
            break
    assert balanceMatch == True
    
    refreshData()
    
    # invalidAccountsFilepath
    with pytest.raises(Exception) as e_info:
        userFileManager.writeToFile("wrongPath")