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
#include <iomanip>
#include <sstream>

using namespace std;

// Classes
#include "User.h"
#include "Game.h"
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

/// <summary>
/// Gets the seller of the game if the game is found in AvailableGames.txt.
/// </summary>
/// <param name="gameName">The name of the game that the current user is trying to buy</param>
/// <returns>string containing the sellers name if the game exists. If not, an empty string.</returns>
string getSellerForGame(string gameName)
{
    ifstream gamesFile("AvailableGames.txt");
    string games;

    while (getline(gamesFile, games)) {

        string storedGame = games.substr(0, 26);
        string storedSeller = games.substr(27, 15);

        // Trim spaces from storedGame and storedSeller
        storedGame.erase(storedGame.find_last_not_of(" ") + 1);
        storedSeller.erase(storedSeller.find_last_not_of(" ") + 1);

        if (storedGame == gameName) {
            gamesFile.close();
            return storedSeller; // Return the seller associated with the game
        }
    }

    gamesFile.close();
    return ""; // Return an empty string if the game is not found
}


/// <summary>
/// Checks if the game is in the AvailableGames.txt.
/// </summary>
/// <param name="gameName">The name of the game that the current user is trying to buy</param>
/// <returns>boolean value indicating whether the game is available to buy.</returns>
bool isValidGame(string gameName)
{
    return !getSellerForGame(gameName).empty();
}

/// <summary>
/// Gets the price of the game the user wants to buy.
/// </summary>
/// <param name="gameName">The name of the game that the current user is trying to buy</param>
/// <returns>string containing the game's price.</returns>
string getGamePrice(const string gameName)
{
    ifstream gamesFile("AvailableGames.txt");
    string gameInfo;

    while (getline(gamesFile, gameInfo))
    {
        string storedGame = gameInfo.substr(0, 26);
        string storedPrice = gameInfo.substr(42, 7);
        storedGame.erase(storedGame.find_last_not_of(" ") + 1);

        if (storedGame == gameName)
        {
            gamesFile.close();
            storedPrice.erase(1, min(storedPrice.find_first_not_of('0') + 1, storedPrice.size() - 1));
            return storedPrice;
        }
    }

    gamesFile.close();
    return "0.00";
}

/// <summary>
/// Update the GameCollection.txt file to remove the game from the buyer.
/// </summary>
/// <param name="buyer">The current user who now owns the game.</param>
/// <param name="gameName">The name of the game that the current user is trying to buy.</param>
void removeGame(string buyer, string gameName)
{
    ifstream inputFile("GameCollection.txt");
    ofstream tempFile("tempGameCollection.txt");

    string line, storedGame, storedOwner;
    while (getline(inputFile, line))
    {
        storedGame = line.substr(0, 26);
        storedGame.erase(storedGame.find_last_not_of(" ") + 1);
        if (storedGame != "END") {
            storedOwner = line.substr(27, 15);
            storedOwner.erase(storedOwner.find_last_not_of(" ") + 1);
        }
        
        if (storedGame != gameName || storedOwner != buyer) {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();
    // Rename temp file to the original file
    remove("GameCollection.txt");
    rename("tempGameCollection.txt", "GameCollection.txt");
}

/**
 * Update the CurrentUserAccounts.txt file to reflect the transfer of credits
 *
 * @param username The username of the account whose balance needs to be updated.
 * @param newBalance The new credit balance of the account.
 */
/// <summary>
/// Update the CurrentUserAccounts.txt file to reflect the transfer of credits.
/// </summary>
/// <param name="username">TThe username of the account whose balance needs to be updated.</param>
/// <param name="newBalance">The new credit balance of the account.</param>
void updateUserBalance(string username, float newBalance)
{
    ifstream inputFile("CurrentUserAccounts.txt");
    ofstream tempFile("temp.txt");

    string line;
    while (getline(inputFile, line))
    {
        string storedUsername = line.substr(0, 15);
        string userType = line.substr(16, 2);
        storedUsername.erase(storedUsername.find_last_not_of(" ") + 1);
        if (storedUsername == username)
        {
            tempFile << setw(16) << left << username << setw(3) << left << userType;
            tempFile << fixed << setprecision(2) << setfill('0') << setw(9) << right << newBalance << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    remove("CurrentUserAccounts.txt");
    rename("temp.txt", "CurrentUserAccounts.txt");
}

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

    // TO-DO::
    // Make sure the END line from previous write is deleted
    // Write to the DailyTransactions file
    ofstream dailyTransactionFile;
    dailyTransactionFile.open("DailyTransactions.txt", ios::app);
    for (int i = 0; i < transactions.size(); i++) {
        dailyTransactionFile << transactions[i].toString(transactions[i]) << "\n";
    }
    dailyTransactionFile << "END\n";
    dailyTransactionFile.close();

    cout << "Thank you for using Vapour. \nGoodbye.";

    exit(0);
};

/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction createUser(User& currentUser) // Transaction code: 1
{
    string newUsername;
    bool nameBool = true;
    string newUserType;
    bool typeBool = true;
    string whitespace;
    int whitespaceLength;

    cout << "Creating new user.. Please input their username: \n";
    // Username input check
    while(nameBool){
        cin >> newUsername;
        if(isValidUser(newUsername)){ cout << "Error! User already exists, please try again:\n"; }
        else if (newUsername.length() > 25){ cout << "Error! Username is longer than 15 characters, please enter a shorter name:\n"; }
        else { nameBool = false;}
    }
    
    // Usertype input check
    cout << "Username accepted! What type of user are they? (AA,FS,SS,BS): \n";
    while(typeBool){
        cin >> newUserType;
        cout << newUserType << "\n";

        for(int j=0;j<2;j++){
            newUserType[j] = toupper(newUserType[j]);
        };
        
        if(newUserType == "AA"){ typeBool = false; }
        else if(newUserType == "FS"){ typeBool = false; }
        else if(newUserType == "SS"){ typeBool = false; }
        else if(newUserType == "BS"){ typeBool = false; }
        else if(newUserType.length() > 2){ cout << "Error! Type can only be AA, FS, SS, BS. Please try again: \n"; }
        else{ cout << "Error! Type does not exit. Acceptable types are AA,FS,SS,BS. Please try again: \n"; }
    }

    // whitespace padding for account name
    for (int i=0; i<(16 - newUsername.length()); i++){
        whitespace += ' ';
    }

    // read from accounts and throw into text;
    string account;
    ofstream textFile;
    textFile.open("temp.txt");
    ifstream accountsFile;
    accountsFile.open("CurrentUserAccounts.txt");
    while(getline(accountsFile,account)){
        if(account != "END"){
        textFile << account << "\n";
        }
    }
    
    // add new account to text;
    textFile << newUsername + whitespace + newUserType + " 000000000";
    textFile << "\nEND";
    remove("CurrentUserAccounts.txt");
    rename("temp.txt","CurrentUserAccounts.txt");
    textFile.close();
    accountsFile.close();
    cout << "User full12345 successfully created! Permissions: buy, sell \n";
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
    bool isValidInput = false;
    string userInput;
    cout << "Please enter the name of the user you want to delete: ";
    while (!isValidInput) {
        cin >> userInput;
        if (currentUser.name == userInput) {
            cout << "Error! You can't delete the current user.";
        }
        else if (!isValidUser(userInput)) {
            cout << "Error! " + userInput + " is not a valid username.";
        }
        else {
            isValidInput = true;
        }
        if (!isValidInput) {
            cout << "Please enter the name of a valid user to delete:";
        }
    }

    string line;
    ifstream usersFile;
    usersFile.open("CurrentUserAccounts.txt");
    ofstream temp("temp.txt");
    while (getline(usersFile, line))
    {
        if (line.substr(0, userInput.length()) != userInput) {
            temp << line << endl;
        }
    }
    remove("CurrentUserAccounts.txt");
    rename("temp.txt", "CurrentUserAccounts.txt");

    usersFile.close();
    temp.close();

    Transaction deleteUserTransaction("delete", currentUser);
    return deleteUserTransaction;
};
/// <summary>
/// Handles buy transaction.
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction buyGame(User& currentUser) // Transaction code: 3
{
    string gameName, seller, log;
    cout << "Please enter the name of the game you would like to buy: ";
    cin.clear();
    std::cin.ignore(100,'\n');
    std::getline(std::cin, gameName);
    cout << "Please enter the seller of " + gameName + ": ";
    cin >> seller;

    string storedSeller = getSellerForGame(gameName);

    // Log to Game Collection file and daily transaction file
    string paddedGameName = gameName.substr(0, 20) + string(20 - gameName.length(), ' ');
    string paddedStoredSeller = storedSeller.substr(0, 15) + string(15 - storedSeller.length(), ' ');
    string paddedBuyerName = currentUser.name.substr(0, 15) + string(15 - currentUser.name.length(), ' ');
    string paddedPrice = getGamePrice(gameName);

    cout << "Purchase successful! Transferring the credit value of " + gameName + " from you to the seller, " + seller + ". You can now find " + gameName + " in your collection!" << endl;
   
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
    string gameName;    // Temporary string to store the name of the game
    float gamePrice;    // Better as an int, then parse and validate input.
    // If they don't enter a decimal, we append 00 before storing
    cout << "Creating new listing. Enter the game's title: ";
    cin >> gameName;
    cout << "Enter the game's price: ";
    //TO-DO:: Input Validation
    cin >> gamePrice;

    Game gameToSell(currentUser, gameName, gamePrice);

    ofstream availableGamesFile;
    availableGamesFile.open("AvailableGames.txt", ios::app);

    // TO-DO:: The below will not delete the "END" from the last file write
    availableGamesFile << "\n" + gameToSell.toString(); // Should do a replace(sellGame.toString(sellGame), "END");
    availableGamesFile << "\nEND";
    availableGamesFile.close();

    // Need to pass a game to our transaction V
    Transaction sellGameTransaction("sell", currentUser, gameToSell);
    return sellGameTransaction;
};
/// <summary>
/// 
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction refundGame(User& currentUser) // Transaction code: 5
{
    string buyer, seller, game, amount, log;
    ostringstream oss;
    cout << "Please enter the buyer's username (the recipient of the refund): ";
    cin >> buyer;
    cout << "Please enter the seller's username: ";
    cin >> seller;
    cout << "Please enter the name of the game you would like to return: ";
    cin.ignore(1000, '\n');
    getline(cin, game);
    cout << "game is: " + game << endl;

    // Remove game from GameCollection.txt
    removeGame(buyer, game);

    cout << "Please enter the amount of credit to transfer to the buyer account: ";
    cin >> amount;

    // Update CurrentUserAccounts.txt
    float buyerBalance = getUserBalance(buyer) + stof(amount);
    float sellerBalance = getUserBalance(seller) - stof(amount);
    updateUserBalance(buyer, buyerBalance);
    updateUserBalance(seller, sellerBalance);

    //cout << "buyer balance: " + to_string(buyerBalance) << endl;
    //cout << "seller balance: " + to_string(sellerBalance) << endl;

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
    string username, amount, userType, log;
    ostringstream oss;
    if (currentUser.type == "AA")
    {
        cout << "Which user would you like to add credit to?";
        cin >> username;
        cout << "How much credit would you like to add to " + username + "'s account?";
        cin >> amount;
        userType = currentUser.type;
    }
    else
    {
        username = currentUser.name;
        cout << "How much credit would you like to add to your account?" << endl;
        cin >> amount;
        userType = getUserType(username);
    }
    float userBalance = getUserBalance(username) + stof(amount);
    updateUserBalance(username, userBalance);
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
    {
        dailyTransactions.push_back(addCredit(currentUser));
    }
    else if (transactionName == "logout")
    {
        logout(dailyTransactions, currentUser);
    }

    // Priveleged Transactions for Admin only
    else if (transactionName == "create" && currentUser.type == "AA")
    {
        dailyTransactions.push_back(createUser(currentUser));
    }
    else if (transactionName == "delete" && currentUser.type == "AA")
    {
        dailyTransactions.push_back(deleteUser(currentUser));
    }
    else if (transactionName == "listusers" && currentUser.type == "AA")
    {
        listUsers();
    }

    // All users, except buystandard can refund and sell
    else if (transactionName == "refund" && currentUser.type != "BS")
    {
        dailyTransactions.push_back(refundGame(currentUser));
    }
    else if (transactionName == "sell" && currentUser.type != "BS")
    {
        dailyTransactions.push_back(sellGame(currentUser));
    }

    // All users, except sellstandard can "buy"
    else if (transactionName == "buy" && currentUser.type != "SS")
    {
        dailyTransactions.push_back(buyGame(currentUser));
    }

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