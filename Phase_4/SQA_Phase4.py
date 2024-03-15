# SQA Phase 4
# Matthew, Ajaane, Peter, Russell

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

# for create 01, delete 02, add credit 06, and end session / logout 00
# XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
# X is two digit code
# U is username (buyer if 2 users in transac)
# T is user type
# C is available credit
# - is a space

# for refund 05
# XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
# X is two digit code
# U is buyer username
# S is seller username
# C is refund credit
# - is a space

# for sell 03
# XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_PPPPPP
# X is two digit code
# I is game name
# S is seller username
# P is game price
# - is a space

# for buy 04
# XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
# X is two digit code
# I is game name
# S is seller username
# U is buyer username
# P is game price
# - is a space