# UserManager.py
#
# Contains the User and UserFileManager classes.
# Processes any Object or File/IO required of CurrentUserAccounts
# 
# Authors: Matthew, Ajaane, Peter, Russell
class User:
    """
    This class is designed to represent the users in the system.

    ...

    Attributes
    ----------
    username : str
        the username of the user
    userType : str
        the type of account the user owns
    credit : str
        the user's credit balance
    """
    
    def __init__(self, username, userType, credit):
        self.username = username
        self.userType = userType
        self.credit = credit

class UserFileManager:
    """
    The UserFileManager class is responsible for managing user-related operations 
    and for file management for the CurrentUserAccounts.txt file.
    
    ...

    Attributes
    ----------
    users : List[User]
        a list of User objects

    Methods
    -------
    getUserByUsername(username)
        Getter function that returns a User object with the given username
        
    readFromFile(filename)
        Reads user data from CurrentUserAccounts.txt and populates the users
        list with User objects created from the data
    
    writeToFile(filename)
        Writes user data from the users list to the specified file. 
        Each user's data is formatted and written as a separate line in the file
        
        
    addUser(username, userType, credit)
        Creates new User object with specified User data and adds it to the user list
        
    removeUse(username)
        Removes the User with the specified username from the user list
        
    updateUsercredit
        Updates the credit of the User with the specified username in the user list by
        adding the creditChange amount

    """
    
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