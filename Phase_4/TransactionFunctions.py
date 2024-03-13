# SQA Phase 4
# Matthew, Ajaane, Peter, Russell

# Classes

from UserManager import UserManager
from GameManager import GameManager
from CollectionManager import CollectionManager

# Helper Functions

from HelperFunctions import parseMost
from HelperFunctions import parseRefund
from HelperFunctions import parseSell
from HelperFunctions import parseBuy

def logout(transaction):
    return
def create(transaction):
    newUser, userType, credit = parseMost(transaction)
    UserManager.createUser(UserManager,newUser,userType,credit)
    return  
def delete(transaction):
    user, userType, credit = parseMost(transaction)
    return  
def sell(transaction):
    return  
def buy(transaction):
    return  
def refund(transaction):
    return   
def addCredit(transaction):
    user, userType, credit = parseMost(transaction)
    userManager = UserManager(user, "", userType, credit, "")
    userManager.updateUserBalance()