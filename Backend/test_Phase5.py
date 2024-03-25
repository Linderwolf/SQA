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

# Specify the file paths for CurrentUserAccounts.txt, AvailableGames.txt, and DailyTransactions.txt
userAccountsFilePath = "CurrentUserAccounts.txt"
availableGameFilePath = "AvailableGames.txt"
gameCollectionFilePath = "GameCollection.txt"
dailyTransactionFilePath = "DailyTransactions.txt"

import os.path

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
# test transaction.create(self, transaction)
# test transaction.delete(self, transaction)
# test transaction.sell(self, transaction)
# test transaction.buy(self, transaction)
# test transaction.refund(self, transaction)
# test transaction.addCredit(self, transaction)


