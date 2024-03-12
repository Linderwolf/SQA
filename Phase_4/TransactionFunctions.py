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

def logout(transaction):
    return
def create(transaction):
    transactionCode,newUser,userType,credit = parseMost(transaction)
    print(newUser)
    return  
def delete(transaction):
    return  
def sell(transaction):
    return  
def buy(transaction):
    return  
def refund(transaction):
    return   
def addCredit(transaction):
    return