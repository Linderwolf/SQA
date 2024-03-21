# HelperFunctions.py
#
# Contains functions that retrieve attributes from strings,
#   Processes Reads & Writes to the GameCollection
# 
# Authors: Matthew, Ajaane, Peter, Russell
import re

def getTransactionCode(transaction):
    return transaction[:2]

# Parsing Methods: 
# Return attributes given an appropriately formatted String
        
# for create 01, delete 02, add credit 06, and end session / logout 00
# XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
# X is two digit code
# U is username (buyer if 2 users in transac)
# T is user type
# C is available credit
# - is a space
def parseMost(line): # for create, delete, add credit, and logout
    newUser, userType, credit = line.split()[1:]
    return newUser, userType, credit


# for refund 05
# XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
# X is two digit code
# U is buyer username
# S is seller username
# C is refund credit
# - is a space
def parseRefund(line):
    pattern = re.compile(r'^(\d{2}) (.{25}) (.{15}) (.{15}) (\d+\.\d{2})$')
    match = pattern.match(line)
    if match:
        transactionCode, gameName, buyer, seller, credit = match.groups()
        gameName = gameName.rstrip()   
        buyer = buyer.rstrip()       
        seller = seller.rstrip()                       
        credit = float(credit) 
    else:
        print(f"Invalid transaction format: |{line}|")
        return None
    return transactionCode, gameName, buyer, seller, credit

# for sell 03
# XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_PPPPPP
# X is two digit code
# I is game name
# S is seller username
# P is game price
# - is a space
def parseSell(line):
    pattern = re.compile(r'^(\d{2}) (.{19}) (.{13}) (\d+\.\d{2})$')
    match = pattern.match(line)
    if match:
        transactionCode, gameName, seller, gamePrice = match.groups()
        gameName = gameName.rstrip() #gameName.match.group(2).strip()
        seller = seller.rstrip()
        gamePrice = float(gamePrice)
    else:
        print(f"Invalid transaction format: |{line}|")
        return None
    return transactionCode, gameName, seller, gamePrice
    
# for buy 04
# XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
# X is two digit code
# I is game name
# S is seller username
# U is buyer username
# P is game price
# - is a space
def parseBuy(line):
    pattern = re.compile(r'^(\d{2}) (.{19}) (.{15}) (.{14}) (\d+\.\d{2})$')
    match = pattern.match(line)
    if match:
        transactionCode, gameName, seller, buyer, gamePrice = match.groups()
        transactionCode = transactionCode
        gameName = gameName.rstrip()        
        seller = seller.rstrip()           
        buyer = buyer.rstrip()              
        gamePrice = float(gamePrice)        
    
    else:
        print(f"Invalid transaction format: |{line}|")
        return None

    return transactionCode, gameName, seller, buyer, gamePrice