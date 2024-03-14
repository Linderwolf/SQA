# SQA Phase 4
# Matthew, Ajaane, Peter, Russell
import re
# Classes
import UserManager
import GameManager
import CollectionManager

def getTransactionCode(transaction):
    return transaction[:2]

def appendToGameCollection(gameName, seller):
    with open('GameCollection.txt', 'r') as file:
        lines = file.readlines()
    # Modify the content by adding a new line
    new_line = f"{gameName:<26} {seller:<15}\n"
    # Find the index of the line with 'END'
    end_index = lines.index('END')
    # Insert the new line before the line with 'END'
    lines.insert(end_index, new_line)
    file.close()

    # Write the modified content back to the file
    with open('GameCollection.txt', 'w') as file:
        file.writelines(lines)
    file.close()
    
def removeGameFromCollection(lineToRemove):
    with open('GameCollection.txt', 'r') as file:
        lines = file.readlines()

    # Find the index of the line to remove
    try:
        index_to_remove = lines.index(lineToRemove)
    except ValueError:
        print(f"Error: Line '{lineToRemove.strip()}' not found in the file.")
        return

    # Remove the line
    lines.pop(index_to_remove)

    # Write the modified content back to the file
    with open('GameCollection.txt', 'w') as file:
        file.writelines(lines)

# Parsing Methods

def parseMost(line): # for create, delete, add credit, and logout
    newUser, userType, credit = line.split()[1:]
    return newUser, userType, credit

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

def parseSell(line):
    pattern = re.compile(r'^(\d{2})) (.{19}) (.{13}) (\d+\.\d{2})$')
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

    #print(f'transCode: {transactionCode} game: {gameName} seller: {seller} buyer: {buyer} gamePrice: {gamePrice}')
    return transactionCode, gameName, seller, buyer, gamePrice

def getUpdatedBalanceString(line, credit):
    updatedBalance = float(line[-9:]) + float(credit)
    return "0" * (9 - len(str(updatedBalance))) + str(updatedBalance)