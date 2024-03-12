# SQA Phase 4
# Matthew, Ajaane, Peter, Russell

# Classes
from UserManager import UserManager
from GameManager import GameManager
from CollectionManager import CollectionManager

#Transaction Functions

from TransactionFunctions import logout
from TransactionFunctions import create
from TransactionFunctions import delete
from TransactionFunctions import sell
from TransactionFunctions import buy
from TransactionFunctions import refund
from TransactionFunctions import addCredit

# Helper Functions

from HelperFunctions import getTransactionCode

# Main

dailyTransactionFile = open("DailyTransactions.txt", "r")

for transaction in dailyTransactionFile:
    if transaction == "END":
        break
    
    transactionCode = getTransactionCode(transaction)
    match transactionCode:
        case "00": logout(transaction)
        case "01": create(transaction) # Russell
        case "02": delete(transaction) # Matthew
        case "03": sell(transaction) # Peter
        case "04": buy(transaction) # Ajaane
        case "05": refund(transaction) # Ajaane
        case "06": addCredit(transaction) # Matthew
        
    
 
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

