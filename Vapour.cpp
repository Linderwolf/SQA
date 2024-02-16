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
#include "Transaction.h"
#include "Game.h"
#include "User.h"

// Global Variables
User currentUser;   // A User object, representing the user currently logged into the system

//stores the transactions performed by a user while logged in
vector<Transaction> dailyTransactions;

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

//void dailyTransactionWrite(vector<Transaction> transactions) {
//    ofstream dailyTransactionFile("DailyTransactions.txt");
//    for (int i = 0; i < transactions.size(); i++) {
//        dailyTransactionFile << transactions[i].toString() << "\n";
//    }
//    dailyTransactionFile.close();
//}

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
                string userType = accounts.substr(15, 2);
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

// Logout Transaction
// If the user is logged in, ends their session.
// Writes their transaction history to the Daily Transaction File
void logout()
{

    cout << "Writing to Daily Transaction File...\n";

    // TO-DO::
    // Write to Daily Transaction File

    cout << "Thank you for using Vapour. \nGoodbye.";

    return;

};

// Transaction Stubs to implement
void addCredit(string userType) {};
void createUser() {};   
void deleteUser() {};   // Matthew
void listUsers() {};    
void buyGame() {};
void sellGame() {}; 
void refundGame() {};
void listGames() {};    

/// <summary>
/// Calls a Transaction function corresponding to a valid string input. Provides an error message for invalid input.
///     -   This function is recursively called until a "Logout()" transaction is processed.
/// </summary>
/// <param name="transaction">: A string input of the transaction a user would like to perform</param>
/// <param name="currentUser">: A User object representing the logged in User</param>
void inputLogic(string transaction, User currentUser) {     

    // TO-DO::
    // Add trimming
    //
    // Iterate over the character array to change each to lowercase.
    for (int i = 0; i < transaction.length(); i++)
        transaction[i] = tolower(transaction[i]);   // tolower() sets input to lowercase

    // TO-DO::
    // Log each transaction
    //
    //  AA FS, BS, SS Valid user Types

    if (transaction == "list")       { listGames(); }  // all

    // All users, except sellstandard can "buy"
    else if (transaction == "buy" && currentUser.type != "SS") { buyGame(); }

    // TO-DO::
    // Clarify requirements. Does it make sense for sellstandard accounts, 
    //                       which cannot make purchases to add credit?
    else if (transaction == "addcredit") { addCredit(currentUser.type); }

    // Priveleged Transactions for Admin only
    else if (transaction == "create" && currentUser.type == "AA") { createUser(); }
    else if (transaction == "delete" && currentUser.type == "AA") { deleteUser(); }
    else if (transaction == "list_users" && currentUser.type == "AA") { listUsers(); }

    // All users, except buystandard can refund and sell
    else if (transaction == "refund" && currentUser.type != "BS") { refundGame(); }
    else if (transaction == "sell" && currentUser.type != "BS") { sellGame(); }
        
    // All users can logout
    else if (transaction == "logout") { logout(); }
    else {
        cout << "Error! Please input a valid command: ";
        cin >> transaction;
        inputLogic(transaction, currentUser);
    }
    cout << "Input another transaction: ";
    cin >> transaction;
    inputLogic(transaction, currentUser);
};

int main(){
    //TO-DO::
    //Implement the useless "login" transaction that's listed in the requirements

    string userInput;   // Holds the text a user will input while logging into the system.

    // Prompt for username to log in.
    cout << "Welcome to Vapour!\nPlease enter your Username: ";
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
    inputLogic(userInput, currentUser);
}