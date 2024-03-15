class User:
    def __init__(self, username, userType, credit):
        self.username = username
        self.userType = userType
        self.credit = credit

class UserFileManager:
    def __init__(self):
        self.users = []
        
    def getUserByUsername(self, username):
        for user in self.users:
            if user.username == username:
                return user
        return None

    def readFromFile(self, filename):
        with open(filename, 'r') as file:
             for line in file:
                parts = line.split()
                if len(parts) == 3:  # Make sure the line has all required fields
                    username, userType, credit = parts
                    newUser = User(username, userType, float(credit))
                    self.users.append(newUser)
        file.close()
        return self.users
            
    # Write to CurrentUserAccounts.txt
    def writeToFile(self, filename):
        with open(filename, 'w') as file:
            for user in self.users:
                line = f"{user.username:<15} {user.userType:<2} {user.credit:09.2f}\n"
                file.write(line)
            file.write("END")
        

    def addUser(self, username, userType, credit):
        newUser = User(username, userType, credit)
        self.users.append(newUser)
        print(f"User {username} added successfully.")

    def removeUser(self, username):
        for user in self.users:
            if user.username == username:
                self.users.remove(user)
                print(f"User {username} removed successfully.")
                return
        print(f"User {username} not found.")

    def updateUsercredit(self, username, creditChange):
        for user in self.users:
            if user.username == username:
                user.credit += creditChange
                print(f"User {username}'s credit updated successfully.")
                return
        print(f"User {username} not found.")



# # Helper Functions

# from HelperFunctions import getUpdatedBalanceString

# class UserManager:
#     # Constructor
#     # Create, Delete, Add Credit: user2 and gameName will be empty strings
#     # Refund: userType and gameName will be empty strings
#     # Buy: userType will be an empty string
#     def __init__(self, user1, user2, userType, credit, gameName):
#         self.user1 = user1
#         self.user2 = user2
#         self.userType = userType
#         self.credit = credit
#         self.gameName = gameName
#         self.filename = "CurrentUserAccounts.txt"

#     def createUser(self):
#         print(self.filename)
#         #print(username)
#         #print(usertype)
#         #print(credit)
#         return
    
#     def deleteUser():
#         return
    
#     def updateUserBalance(self):
#         accountsFile = open(self.filename, "r")
#         accounts = accountsFile.readlines()
#         lineNum = 0
        
#         for account in accountsFile:
#             lineNum += 1
#             if account[:len(self.user1)] == self.user1:
#                 updatedBalance = getUpdatedBalanceString(account, self.credit)
#                 accounts[lineNum] = account.replace(self.credit, updatedBalance) + "\n"
#                 break
            
#         accountsFile = open(self.filename, "w")
#         accountsFile.writelines(accounts)
                
#         accountsFile.close()