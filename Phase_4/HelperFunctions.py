# SQA Phase 4
# Matthew, Ajaane, Peter, Russell

# Classes
import UserManager
import GameManager
import CollectionManager

def getTransactionCode(transaction):
    return transaction[:2]

def parseMost(line): # for create, delete, add credit, and logout
    transactionCode,newUser,userType,credit = line.split()
    # print("new username is: " + newUser)
    # print("user type is: " + userType)
    return transactionCode,newUser,userType,credit

def parseRefund(line):
    transactionCode,buyer,seller,credit = line.split()
    return transactionCode,buyer,seller,credit

def parseSell(line):
    transactionCode,gameName,seller,gamePrice = line.split()
    return transactionCode,gameName,seller,gamePrice

def parseBuy(line):
    transactionCode,gameName,seller,buyer,gamePrice = line.split()
    return transactionCode,gameName,seller,buyer,gamePrice