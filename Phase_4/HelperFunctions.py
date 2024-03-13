# SQA Phase 4
# Matthew, Ajaane, Peter, Russell

# Classes
from UserManager import UserManager
from GameManager import GameManager
from CollectionManager import CollectionManager

def getTransactionCode(transaction):
    return transaction[:2]

def parseMost(line): # for create, delete, add credit, and logout
    newUser, userType, credit = line.split()[1:]
    return newUser, userType, credit

def parseRefund(line):
    buyer, seller, credit = line.split()[1:]
    return buyer, seller, credit

def parseSell(line):
    gameName,seller,gamePrice = line.split()[1:]
    return gameName, seller, gamePrice

def parseBuy(line):
    gameName, seller, buyer, gamePrice = line.split()[1:]
    return gameName, seller, buyer, gamePrice

def getUpdatedBalanceString(line, credit):
    updatedBalance = float(line[-9:]) + float(credit)
    return "0" * (9 - len(str(updatedBalance))) + str(updatedBalance)