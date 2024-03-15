# SQA_Phase4.py
#
# The Main file. Sets up file variables, and reads transactions from DailyTransactions files for processing 
# 
# Authors: Matthew, Ajaane, Peter, Russell
# Classes
from UserManager import UserFileManager
from GameManager import AvailableGamesFileManager
from TransactionFunctions import TransactionManager

# Specify the file paths for CurrentUserAccounts.txt, AvailableGames.txt, and DailyTransactions.txt
userAccountsFilePath = "CurrentUserAccounts.txt"
availableGameFilePath = "AvailableGames.txt"
dailyTransactionFilePath = "DailyTransactions.txt"

# Create instances of FileManager and TransactionManager objects
userFileManager = UserFileManager()
gameFileManager = AvailableGamesFileManager()
transactionManager = TransactionManager(userFileManager, gameFileManager)

# Read user data from the file
userFileManager.readFromFile(userAccountsFilePath)
# Read available games data from the file
gameFileManager.readAvailableGames(availableGameFilePath)

# Process daily transactions
with open(dailyTransactionFilePath, "r") as dailyTransactionFile:
    for transaction in dailyTransactionFile:
        if transaction.strip() == "END":
            break
        transactionManager.processTransaction(transaction)

dailyTransactionFile.close()