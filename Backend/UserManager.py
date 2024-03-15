# UserManager.py
#
# Contains the User and UserFileManager classes.
# Processes any Object or File/IO required of CurrentUserAccounts
# 
# Authors: Matthew, Ajaane, Peter, Russell
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