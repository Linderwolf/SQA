# SQA_Phase4.py
#
# The Main file. Sets up file variables, and reads transactions from DailyTransactions files for processing 
# 
# Authors: Matthew, Ajaane, Peter, Russell
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

# Create instances of FileManager and TransactionManager objects
userFileManager = UserFileManager()
gameFileManager = AvailableGamesFileManager()
gameCollectionManager = GameCollectionManager()
transactionManager = TransactionManager(userFileManager, gameFileManager, gameCollectionManager)

# Read user data from the file
userFileManager.readFromFile(userAccountsFilePath)
# Read available games data from the file
gameFileManager.readAvailableGames(availableGameFilePath)
# Read game collection data from the file
gameCollectionManager.readCollection(gameCollectionFilePath)


# Process daily transactions
with open(dailyTransactionFilePath, "r") as dailyTransactionFile:
    for transaction in dailyTransactionFile:
        if transaction.strip() == "END":
            break
        transactionManager.processTransaction(transaction)

dailyTransactionFile.close()