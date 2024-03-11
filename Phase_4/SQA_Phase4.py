# SQA Phase 4
# Matthew, Ajaane, Peter, Russell

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
        case "01": create(transaction)
        case "02": delete(transaction)
        case "03": sell(transaction)
        case "04": buy(transaction)
        case "05": refund(transaction)
        case "06": addCredit(transaction)
        
    
 


