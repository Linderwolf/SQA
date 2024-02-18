/**   
 @file Vapour.cpp
 @brief Vapour: A video game distribution service and storefront - Software Quality Assurance Console Application
 @authors Peter Wolfgang Linder, Matthew , Ajaane , Russel
 @date February 2024
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Classes
#include "Game.h"
#include "User.h"
#include "Transaction.h"

/// <summary>
/// Compares an input string against the list of all Users.
/// </summary>
/// <returns>A boolean value: whether the user input is contained in the system (true), or not (false)</returns>
bool isValidUser(string user) {
    ifstream accountsFile("CurrentUserAccounts.txt");
    string accounts;

    while (getline(accountsFile, accounts)) {
        string rawUser = accounts.substr(0, 15);
        string storedUsername;
        for (int i = 0; i < rawUser.length(); i++) {
            if (rawUser[i] != ' ') {
                storedUsername += rawUser[i];
            }
        }

        if (storedUsername == user) 
        {
            accountsFile.close();
            return true; 
        }
    }
    accountsFile.close();
    return false;
};

///<summary>
/// Given a valid username string, gets their type from the accounts file
///</summary>
///<returns>The 2-letter code for the type of user: AA, FS, SS, BS for admin, fullstandard, sellstandard, and buystandard, respectively</returns>
///<param name="username">: the username of the User whose type is desired.</param>
string getUserType(string username) {
    if (isValidUser(username)) {
        ifstream accountsFile("CurrentUserAccounts.txt");
        string accounts;

        while (getline(accountsFile, accounts)) {
            string rawUser = accounts.substr(0, 15);
            string storedUsername;
            for (int i = 0; i < rawUser.length(); i++) {
                if (rawUser[i] != ' ') {
                    storedUsername += rawUser[i];
                }
            }
            // cout << storedUsername << "\n";
            if (storedUsername == username) {
                string userType = accounts.substr(16, 2);
                accountsFile.close();
                return userType;
            }
        }
        return "invalid user";
    }
    else { return "invalid user"; };
};

///<summary>
/// Given a valid username string, gets the user's account balance from the accounts file
///</summary>
///<returns>The user's balance as a float.
///Returns a value of -1.0 if the provided username string is not valid.</returns>
float getUserBalance(string username) {
    if (isValidUser(username)) {
        ifstream accountsFile("CurrentUserAccounts.txt");
        string accounts;

        while (getline(accountsFile, accounts)) {
            string rawUser = accounts.substr(0, 15);
            string storedUsername;
            for (int i = 0; i < rawUser.length(); i++) {
                if (rawUser[i] != ' ') {
                    storedUsername += rawUser[i];
                }
            }
            // cout << storedUsername << "\n";
            if (storedUsername == username) {
                string rawBalance = accounts.substr(18, 9);
                float userBalance = stof(rawBalance);
                accountsFile.close();
                return userBalance;
            }
        }
        return -1.0;
    }
    else { return -1.0; };
};

#pragma region "Transaction Functions"

/// <summary>
/// Ends a User's session and logs them out.
/// Writes their transaction history to the Daily Transaction File.
/// </summary>
/// <param name="transactions">A reference to the vector of transactions performed by the User</param>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
void logout(vector<Transaction>& transactions, User& currentUser)
{
    Transaction logoutTransaction("endofsession", currentUser);   // Create a new logout Transaction
    transactions.push_back(logoutTransaction);     // Add the logout Transaction to the vector

    cout << "Writing to Daily Transaction File...\n";

    // Write to the DailyTransactions file
    ofstream dailyTransactionFile("DailyTransactions.txt");
    for (int i = 0; i < transactions.size(); i++) {
        dailyTransactionFile << transactions[i].ToString(transactions[i]) << "\n";
    }
    dailyTransactionFile << "END";
    dailyTransactionFile.close();

    cout << "Thank you for using Vapour. \nGoodbye.";

    return;
};

// Transaction Stubs to implement
// Likely need to pass the user/game as a parameter

/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction createUser(User& currentUser) // Transaction code: 1
{
    Transaction createUserTransaction("create", currentUser);
    return createUserTransaction;
};   
/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction deleteUser(User& currentUser)  // Transaction code: 2
{
    Transaction deleteUserTransaction("delete", currentUser);
    return deleteUserTransaction;
};
/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction buyGame(User& currentUser) // Transaction code: 3
{
    // Need to pass a game to our transaction V
    Transaction buyGameTransaction("buy", currentUser);
    return buyGameTransaction;
};
/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction sellGame(User& currentUser) // Transaction code: 4
{
    // Need to pass a game to our transaction V
    Transaction sellGameTransaction("sell", currentUser);
    return sellGameTransaction;
}; 
/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction refundGame(User& currentUser) // Transaction code: 5
{
    Transaction refundGameTransaction("refund", currentUser);
    return refundGameTransaction;
};
/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction addCredit(User& currentUser) // Transaction code: 6
{
    Transaction addCreditTransaction("addcredit", currentUser);
    return addCreditTransaction;
};

/// <summary>
/// Prints the list of users and their information in the system
/// </summary>
void listUsers() {
    ifstream accountsFile("CurrentUserAccounts.txt");
    string accounts;
    cout << "\nUsername    | Type | Balance\n";
    cout << "============================\n";
    while (getline (accountsFile, accounts)) {
            cout << accounts << "\n";
    }
};

/// <summary>
/// Prints the list of games and their information in the system
/// </summary>
void listGames() {
    ifstream gamesFile("AvailableGames.txt");
    string games;
    cout << "\nGame Name                | Seller         | Price\n";
    cout << "=================================================\n";
    while (getline (gamesFile, games)) {
            cout << games << "\n";
    }
};    
#pragma endregion "Transaction Functions"

/// <summary>
/// Calls a Transaction function corresponding to a valid string input.
/// Builds a vector of Transactions for writing to the DailyTransactions.txt file. 
/// This function is recursively called until a "Logout()" transaction is processed.
/// </summary>
/// <param name="transaction">: A string input of the transaction a user would like to perform</param>
/// <param name="currentUser">: A reference to the User object representing the logged-in User</param>
/// <param name="dailyTransactions">: Reference vector to list transactions the logged-in User has performed.</param>
void inputLogic(string transactionName, User& currentUser, vector<Transaction>& dailyTransactions) {
    string messageString = "";

    // Iterate over the input character array to change each to lowercase.
    for (int i = 0; i < transactionName.length(); i++)
        transactionName[i] = tolower(transactionName[i]);   // tolower() sets input to lowercase

    // Valid user types: AA FS, BS, SS (admin, fullstandard, buystandard, sellstandard)
    
    if (transactionName == "list") { listGames(); } // All users can list games
    // TO-DO::
    // Clarify requirements. Does addcredit() make sense for sellstandard accounts, 
    //                       which cannot make purchases to add credit?...
    else if (transactionName == "addcredit")
        { dailyTransactions.push_back(addCredit(currentUser)); }
    else if (transactionName == "logout")
        { logout(dailyTransactions, currentUser); }

    // Priveleged Transactions for Admin only
    else if (transactionName == "create" && currentUser.type == "AA")
        { dailyTransactions.push_back(createUser(currentUser)); }
    else if (transactionName == "delete" && currentUser.type == "AA")
        { dailyTransactions.push_back(deleteUser(currentUser)); }
    else if (transactionName == "listusers" && currentUser.type == "AA")
        { listUsers(); }

    // All users, except buystandard can refund and sell
    else if (transactionName == "refund" && currentUser.type != "BS")
        { dailyTransactions.push_back(refundGame(currentUser)); }
    else if (transactionName == "sell" && currentUser.type != "BS")
        { dailyTransactions.push_back(sellGame(currentUser)); }
    
    // All users, except sellstandard can "buy"
    else if (transactionName == "buy" && currentUser.type != "SS")
        { dailyTransactions.push_back(buyGame(currentUser)); }
    
    else { messageString = transactionName + " is not a valid transaction.\n"; }

    messageString += "Input another transaction: ";
    cout << messageString;
    cin >> transactionName;
    inputLogic(transactionName, currentUser, dailyTransactions);   // Recur until Logout()
};

int main(){
    //TO-DO::
    //Implement the useless "login" transaction that's listed in the requirements

    string userInput;   // Holds the text a user will input while logging into the system.
    vector<Transaction> dailyTransactions;  // Stores the transactions performed by a user while logged in

    // Prompt for username to log in.
    cout << "Welcome to Vapour!\nPlease enter your Username to log in: ";
    cin >> userInput;

    // Wait for valid input before proceding
    while (!isValidUser(userInput)) {
        cout << userInput + " is not a valid username.\nPlease enter a valid username: ";
        cin >> userInput;
    }

    // Create a User object with the provided, valid input, and corresponding user data.
    User currentUser = User(userInput, getUserType(userInput), getUserBalance(userInput));

    // The user is now logged in. Prompt to enter a transaction.
    cout << "Welcome " + currentUser.name + "! Please enter a transaction: ";
    cin >> userInput;

    // The user can now enter transaction codes and complete transactions
    inputLogic(userInput, currentUser, dailyTransactions);

    return 0;
}