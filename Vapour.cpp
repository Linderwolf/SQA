/**   
 @file Vapour.cpp
 @brief Vapour: A video game distribution service and storefront console application - Software Quality Assurance Final
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
bool isLoggedIn;    // Whether the current user has logged in
User currentUser;   // The user currently logged into the system

/// <summary>
/// Compares an input string vs the list of all Users
/// </summary>
/// <returns>A boolean value: whether the user input is contained in the system</returns>
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

// getUserType()
// returns the type of user as a string
// AA, FS, SS, BS
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

// returns the user's balance as a float
// returns -1.0 if the user is invalid
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
    isLoggedIn = false;         // Flip the boolean value
    currentUser.ClearUser();    // Clear the user's attributes
    
    // TO-DO::
    // Write to Daily Transaction File
};


void inputLogic(string transaction) {       // TO-DO:: This will loop infinitely, if logout isn't what's entered.
    // better to recur, than while loop, I think
    // 
    // 
    // Add trimming

    for (int i = 0; i < transaction.length(); i++)  // tolower() sets input to lowercase
        transaction[i] = tolower(transaction[i]);

    if (isLoggedIn) {

        // Log each transaction

        //if (transaction == "list")       { listGames(); }  // all
        //if (transaction == "buy")        { buyGame(); }    // buy-standard, full-standard, admin
        //if (transaction == "addcredit")  { addCredit(); }  // priveleged
        //if (transaction == "create")     { createUser(); } // priveleged
        //if (transaction == "delete")     { deleteUseR(); } // priveleged
        //if (transaction == "list_users") { listUsers(); }  // priveleged
        //if (transaction == "refund")     { refundGame(); } // sell-standard, full-standard, admin
        //if (transaction == "sell")       { sellGame(); }   // sell-standard, full-standard, admin
        
        if (transaction == "logout") { logout(); }
        else {
            cout << "Error! Please input a valid command: ";
            cin >> transaction;
        }
        //inputLogic(transaction);
    }
};

int main(){

    string userInput;

    cout << "Welcome to Vapour!\nPlease enter your Username: ";
    cin >> userInput;

    while (!isValidUser(userInput)) {
        //error message - request input
        cout << userInput + " is not a valid username.\nPlease enter a valid username: ";
        cin >> userInput;
    }
    // Input must be valid here.
        // set User object username to 'user' input
        // Read file
        // set User object 

    User currentUser = User(userInput, getUserType(userInput), getUserBalance(userInput));
    // Create session
    isLoggedIn = true;

    //cout << currentUser.name + " " + currentUser.type + " " + to_string(currentUser.credit);

    cout << "Welcome " + currentUser.name + "! As a " + /*currentUser.getUserTypeVerbose()*/ + " you can:\n";
    cin >> userInput;

    inputLogic(userInput);
}