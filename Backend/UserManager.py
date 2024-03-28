# UserManager.py
#
# Contains the User and UserFileManager classes.
# Processes any Object or File/IO required of CurrentUserAccounts
# 
# Authors: Matthew, Ajaane, Peter, Russell

import os
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
    credit : float
        the user's credit balance
    """
    # A constructor creating a new User object with the specified values
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
        
    removeUser(username)
        Removes the User with the specified username from the user list
        
    updateUsercredit(self, username, creditChange)
        Updates the credit of the User with the specified username in the user list by
        adding the creditChange amount

    """
    
    def __init__(self):
        self.users = []
        
    # Getter function that returns a User object with the given username
    def getUserByUsername(self, username):
        for user in self.users:
            if user.username == username:
                return user
        return None

    # Reads user data from CurrentUserAccounts.txt and populates users from the data
    def readFromFile(self, filename):
        if not os.path.exists(filename):
            raise IOError("ERROR: Fatal Error - File '{filename}' not found.")
        with open(filename, 'r') as file:
             for line in file:
                parts = line.split()
                if len(parts) == 3:  # Make sure the line has all required fields
                    username, userType, credit = parts
                    newUser = User(username, userType, float(credit))
                    self.users.append(newUser)
        file.close()
        return self.users
            
    # Writes users to CurrentUserAccounts.txt after formatting
    def writeToFile(self, filename):
        if not os.path.isfile(filename):
            raise IOError("ERROR: Fatal Error - File '{filename}' not found.")
        with open(filename, 'w') as file:
            for user in self.users:
                line = f"{user.username:<15} {user.userType:<2} {user.credit:09.2f}\n"
                file.write(line) 
            file.write("END")
        
    # Creates new User object with specified User data and adds it to the user list
    def addUser(self, username, userType, credit):
        # Constraint: no user should ever have a negative account balance
        if (credit < 0):           
            return "ERROR: Violation of Constraint: Credit cannot be less than 0."
        # Constraint: a newly created user must have a name different from all existing users
        for user in self.users:
            if user.username == username:
                return "ERROR: Violation of Constraint: User with the same username already exists."
        newUser = User(username, userType, credit)
        
        self.users.append(newUser)
        print(f"User {username} added successfully.")
        return None

    # Removes the User with the specified username from the user list
    def removeUser(self, username):
        for user in self.users:
            if user.username == username:
                self.users.remove(user)
                print(f"User {username} removed successfully.")
                return
        print(f"User {username} not found.")

    # Updates the credit of the User with the specified username by adding the creditChange amount
    def updateUsercredit(self, username, creditChange):
        for user in self.users:
            if user.username == username:
                # Constraint: no user should ever have a negative account balance
                if (user.credit + creditChange < 0):           
                    return "ERROR: Violation of Constraint: Credit cannot be less than 0."
                user.credit += creditChange
                print(f"User {username}'s credit updated successfully.")
                return None
        print(f"User {username} not found.")