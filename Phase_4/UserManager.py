# Helper Functions

from HelperFunctions import getUpdatedBalanceString

class UserManager:
    # Constructor
    # Create, Delete, Add Credit: user2 and gameName will be empty strings
    # Refund: userType and gameName will be empty strings
    # Buy: userType will be an empty string
    def __init__(self, user1, user2, userType, credit, gameName):
        self.user1 = user1
        self.user2 = user2
        self.userType = userType
        self.credit = credit
        self.gameName = gameName
        self.filename = "CurrentUserAccounts.txt"

    def createUser(self):
        print(self.filename)
        #print(username)
        #print(usertype)
        #print(credit)
        return
    
    def deleteUser():
        return
    
    def updateUserBalance(self):
        accountsFile = open(self.filename, "r")
        accounts = accountsFile.readlines()
        lineNum = 0
        
        for account in accountsFile:
            lineNum += 1
            if account[:len(self.user1)] == self.user1:
                updatedBalance = getUpdatedBalanceString(account, self.credit)
                accounts[lineNum] = account.replace(self.credit, updatedBalance) + "\n"
                break
            
        accountsFile = open(self.filename, "w")
        accountsFile.writelines(accounts)
                
        accountsFile.close()