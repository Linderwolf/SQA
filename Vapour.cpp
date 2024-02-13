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

// Classes
#include "Transaction.h"
#include "Game.h"
#include "User.h"

using namespace std;



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

void inputLogic(string transaction) {
    // Add trimming & toLower
    if (transaction == "addcredit")       { addCredit(); }
    else if (transaction == "buy")        { buyGame(); }
    else if (transaction == "create")     { createUser(); }
    else if (transaction == "delete")     { deleteUseR(); }
    else if (transaction == "list")       { listGames(); }
    else if (transaction == "list_users") { listUsers(); }
    else if (transaction == "refund")     { refundGame(); }
    else if (transaction == "sell")       { sellGame(); }
    else if (transaction == "logout")     { logout(); }
    else {
        cout << "Error! Please input a valid command: ";
        cin >> transaction;
        inputLogic(transaction);
    }
};

int main(){

    cout << "Welcome to Vapour!\nPlease enter your Username: ";
    string userInput;
    cin >> userInput;

    while (!isValidUser(userInput)) {
        //error message - request input
        cout << userInput + " is not a valid username.\nPlease enter a valid username: ";
        cin >> userInput;
    }
    cout << "Welcome " + userInput + ", how may we help you?/n";
    cin >> userInput;
    inputLogic(userInput);
}