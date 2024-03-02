/**
 @file Vapour.cpp
 @brief Vapour: A video game distribution service and storefront - Software Quality Assurance Console Application
 @authors Peter Wolfgang Linder, Matthew , Ajaane , Russel
 @date February 2024
*/

// TO-DO::
//
// Refactor: Organize functions into separate .cpp files
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <regex>

using namespace std;

// Classes
#include "User.h"
#include "Game.h"
#include "Transaction.h"

/// <summary>
/// Compares an input string against the list of all Users.
/// </summary>
/// <returns>A boolean value: whether the user input is contained in the system (true), or not (false)</returns>
bool isValidUser(string user)
{
    ifstream accountsFile("CurrentUserAccounts.txt");
    string accounts;

    while (getline(accountsFile, accounts))
    {
        string rawUser = accounts.substr(0, 15);
        string storedUsername;
        for (int i = 0; i < rawUser.length(); i++)
        {
            if (rawUser[i] != ' ')
            {
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

///< summary>
/// Given a valid username string, gets their type from the accounts file
///</summary>
///< returns>The 2-letter code for the type of user: AA, FS, SS, BS for admin, fullstandard, sellstandard, and buystandard, respectively</returns>
///< param name="username">: the username of the User whose type is desired.</param>
string getUserType(string username)
{
    if (isValidUser(username))
    {
        ifstream accountsFile("CurrentUserAccounts.txt");
        string accounts;

        while (getline(accountsFile, accounts))
        {
            string rawUser = accounts.substr(0, 15);
            string storedUsername;
            for (int i = 0; i < rawUser.length(); i++)
            {
                if (rawUser[i] != ' ')
                {
                    storedUsername += rawUser[i];
                }
            }
            // cout << storedUsername << "\n";
            if (storedUsername == username)
            {
                string userType = accounts.substr(16, 2);
                accountsFile.close();
                return userType;
            }
        }
        return "invalid user";
    }
    else
    {
        return "invalid user";
    };
};

///< summary>
/// Given a valid username string, gets the user's account balance from the accounts file
///</summary>
///< returns>The user's balance as a float.
/// Returns a value of -1.0 if the provided username string is not valid.</returns>
float getUserBalance(string username)
{
    if (isValidUser(username))
    {
        ifstream accountsFile("CurrentUserAccounts.txt");
        string accounts;

        while (getline(accountsFile, accounts))
        {
            string rawUser = accounts.substr(0, 15);
            string storedUsername;
            for (int i = 0; i < rawUser.length(); i++)
            {
                if (rawUser[i] != ' ')
                {
                    storedUsername += rawUser[i];
                }
            }
            // cout << storedUsername << "\n";
            if (storedUsername == username)
            {
                string rawBalance = accounts.substr(18, 9);
                float userBalance = stof(rawBalance);
                accountsFile.close();
                return userBalance;
            }
        }
        return -1.0;
    }
    else
    {
        return -1.0;
    };
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

    while (getline(gamesFile, games))
    {

        string storedGame = games.substr(0, 26);
        // Trim spaces from storedGame
        storedGame.erase(storedGame.find_last_not_of(" ") + 1);
        if (storedGame == "END")
        {
            gamesFile.close();
            return "";
        }
        string storedSeller = games.substr(27, 15);
        // Trim spaces from storedSeller
        storedSeller.erase(storedSeller.find_last_not_of(" ") + 1);

        if (storedGame == gameName)
        {
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
/// Checks if the game is currently in AvailableGames.txt.
/// </summary>
/// <param name="gameName">The name of the game that the current user is trying to put for sale.</param>
/// <returns>boolean value indicating whether the game name is taken.</returns>
bool inStore(string gameName)
{
    ifstream availableGamesFile("AvailableGames.txt");
    string availableGames;

    while (getline(availableGamesFile, availableGames))
    {
        string storedGame = availableGames.substr(0, 26);
        storedGame.erase(storedGame.find_last_not_of(" ") + 1);

        if (storedGame == "END")
        {
            availableGamesFile.close();
            return false;
        }

        if (gameName == storedGame)
        {
            return true;
        }
    }

    availableGamesFile.close();
    return false;
}

/// <summary>
/// Checks if the game is currently in the current user's game collection.
/// </summary>
/// <param name="gameName">The name of the game that the current user is trying to buy</param>
/// <returns>boolean value indicating whether the game is already in the user's collection.</returns>
bool isInCollection(string gameName, User currentUser)
{
    ifstream gameCollectionFile("GameCollection.txt");
    string gameCollection;

    bool alreadyInCollection = false;

    while (getline(gameCollectionFile, gameCollection))
    {
        string storedGame = gameCollection.substr(0, 26);
        storedGame.erase(storedGame.find_last_not_of(" ") + 1);

        if (storedGame == "END")
        {
            gameCollectionFile.close();
            return alreadyInCollection;
        }

        string storedUser = gameCollection.substr(27, 15);
        storedUser.erase(storedUser.find_last_not_of(" ") + 1);

        if (storedGame == gameName && storedUser == currentUser.name)
        {
            alreadyInCollection = true;
            break;
        }
    }

    gameCollectionFile.close();
    return alreadyInCollection;
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
/// Update the GameCollection.txt file to include the newly bought game.
/// </summary>
/// <param name="buyer">The current user who now owns the game.</param>
/// <param name="gameName">The name of the game that the current user is trying to buy.</param>
void logGameCollection(string gameName, string buyer)
{

    // Read existing content of GameCollection.txt
    ifstream readFile("GameCollection.txt");
    ofstream writeFile("temp.txt");

    if (!readFile.is_open() || !writeFile.is_open())
    {
        cout << "Error: Unable to open files for reading or writing." << endl;
        return;
    }

    string line;
    while (getline(readFile, line))
    {
        if (line == "END")
        {
            writeFile << setw(26) << left << gameName << " " << setw(15) << left << buyer << " " << endl;
        }
        writeFile << line << endl;
    }

    readFile.close();
    writeFile.close();

    // Replace the original file with the modified content
    remove("GameCollection.txt");
    rename("temp.txt", "GameCollection.txt");
}

/// <summary>
/// Update the GameCollection.txt file to remove the game from the buyer.
/// </summary>
/// <param name="owner">The user who owns the game.</param>
/// <param name="gameName">The name of the game that is being removed.</param>
void removeGame(string owner, string gameName)
{
    ifstream inputFile("GameCollection.txt");
    ofstream tempFile("tempGameCollection.txt");

    if (!inputFile.is_open() || !tempFile.is_open())
    {
        cout << "Error: Unable to open files for reading or writing." << endl;
        return;
    }

    string line, storedGame, storedOwner;
    while (getline(inputFile, line))
    {
        storedGame = line.substr(0, 26);
        storedGame.erase(storedGame.find_last_not_of(" ") + 1);
        if (storedGame != "END")
        {
            storedOwner = line.substr(27, 15);
            storedOwner.erase(storedOwner.find_last_not_of(" ") + 1);
        }

        if (storedGame != gameName || storedOwner != owner)
        {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();
    // Rename temp file to the original file
    remove("GameCollection.txt");
    rename("tempGameCollection.txt", "GameCollection.txt");
}


/// <summary>
/// Update the CurrentUserAccounts.txt file to reflect the transfer of credits.
/// </summary>
/// <param name="username">TThe username of the account whose balance needs to be updated.</param>
/// <param name="newBalance">The new credit balance of the account.</param>
void updateUserBalance(string username, double newBalance)
{
    ifstream inputFile("CurrentUserAccounts.txt");
    ofstream tempFile("temp.txt");
    string line;
    string userType;
    while (getline(inputFile, line))
    {
        string storedUsername = line.substr(0, 15);       
        storedUsername.erase(storedUsername.find_last_not_of(" ") + 1);

        if (storedUsername != "END")  {
            userType = line.substr(16, 2);
        }

        
        if (storedUsername == username) {
            tempFile << setw(16) << left << username << setw(3) << left << userType;
            tempFile << fixed << setprecision(2) << setfill('0') << setw(9) << right << newBalance << endl;
        }
        else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    remove("CurrentUserAccounts.txt");
    rename("temp.txt", "CurrentUserAccounts.txt");
}

/// <summary>
/// Determine if user wants to proceed with refund after warning.
/// </summary>
/// <returns>Boolean value indicating whether the user wants to proceed with the transaction.</returns>
bool shouldProceed()
{
    string proceed;
    bool proceedFlag;
    cout << "Do you still want a refund (y/N)? ";
    while (true)
    {
        cin >> proceed;

        transform(proceed.begin(), proceed.end(), proceed.begin(), ::tolower);
        if ((proceed == "y") || (proceed == "yes"))
        {
            proceedFlag = true;
            break;
        }
        else if ((proceed == "n") || (proceed == "no"))
        {
            proceedFlag = false;
            break;
        }
        else
        {
            cout << "Please enter either yes to proceed with the transaction or no to cancel the transaction: ";
        }
    }
    return proceedFlag;
}

/// <summary>
/// Handles username input from user.
/// </summary>
/// <param name="prompt">Prompt to be displayed to the user, asking for a username.</param>
/// <returns> String containing the valid username.</returns>
string getValidUsernameInput(const string &prompt)
{
    string username;
    bool validUsername = false;

    do
    {
        cout << prompt;
        cin >> username;
        validUsername = isValidUser(username);

        if (!validUsername)
        {
            cout << "Error: " << username << " not found. Please enter a valid user." << endl;
        }

    } while (!validUsername);

    return username;
}

/// <summary>
/// Handles game name input from user. Checks if buyer, seller, and game are associated.
/// </summary>
/// <param name="buyer">The username of the buyer.</param>
/// <param name="seller">The username of the seller.</param>
/// <returns> String containing the valid game name.</returns>
string getValidGameName(const string &buyer, const string &seller)
{
    string game;
    bool validGame = false;
    User buyerUser = User(buyer, getUserType(buyer), getUserBalance(buyer));

    do
    {
        cout << "Please enter the name of the game you would like to return: ";
        cin.ignore(1000, '\n');
        getline(cin, game);

        if (game == "exit")
        {
            break;
        }

        validGame = isValidGame(game);

        if (!validGame)
        {
            cout << "Please enter a valid game to refund." << endl;
        }

        // Buyer doesn’t have the specified game in their game collection
        if (!isInCollection(game, buyerUser)) {
            validGame = false;
            cout << "Error: " << buyer << " does not have " << game << " in their game collection." << endl;
        }
        else {
            // Buyer did not buy the game from the specified seller
            string storedSeller = getSellerForGame(game);
            // KEEP ASKING FOR GAME NAME OR GO BACK TO ASKING FOR BUYER NAME???
            // Repeatedly asking for a game is fine. I've added a quick breakout
            if ((storedSeller != seller))
            {
                validGame = false;
                cout << "Error: " << buyer << " did not buy " << game << " from seller, " << seller + "." << endl;
            }
        }
    } while (!validGame);

    return game;
}

/// <summary>
/// Handles refund amount input from user. Checks if price entered by user and price
/// stored in AvailableGames.txt are consistent.
/// </summary>
/// <param name="game">The name of the game to be refunded.</param>
/// <returns> String containing the valid refund amount.</returns>
string getValidRefundAmount(const string &game)
{
    string amount;
    bool validAmount = false;

    do
    {
        cout << "Please enter the amount of credit to transfer to the buyer account: ";
        cin >> amount;

        string price = getGamePrice(game);

        if (stod(price) != stod(amount))
        {
            cout << "Error: Credit value inconsistent with the value the game was bought for. Please enter the credit value of the game." << endl;
            validAmount = false;
        }
        else
        {
            validAmount = true;
        }

    } while (!validAmount);

    return amount;
}

/// <summary>
/// Checks if a user's balance is about to exceed the maximum. If so, issues a warning.
/// </summary>
/// <param name="username">The username of the account whose balance is being updated.</param>
/// <param name="amount">The amount to be added.</param>
/// <returns> Boolean value indicating if the balance will exceed the maximum (999 999).</returns>
bool shouldWarnUserBalance(const string &username, const string &amount)
{
    float userBalance = getUserBalance(username);

    if (userBalance >= 999999.99)
    {
        cout << "Warning: " << username << " has the maximum amount of credits possible (999,999) and cannot add more to their balance." << endl;
        return true;
    }
    else if (userBalance + stof(amount) > 999999.99)
    {
        cout << "Warning: If refund is added, " << username << " will exceed the maximum amount of credits possible (999,999). Cannot add more to their balance after max is reached." << endl;
        return true;
    }

    return false;
}

/// <summary>
/// Checks if user has enough credits.
/// </summary>
/// <param name="seller">The username of the user.</param>
/// <param name="amount">The amount to be added.</param>
/// <returns> Boolean value indicating if the balance of the user is greater than the amount.</returns>
bool isUserBalanceSufficient(const string &user, const string &amount)
{
    float sellerBalance = getUserBalance(user);
    return (sellerBalance >= stod(amount));
}


#pragma region "Transaction Functions"

/// <summary>
/// Ends a User's session and logs them out.
/// Writes their transaction history to the Daily Transaction File.
/// </summary>
/// <param name="transactions">A reference to the vector of transactions performed by the User</param>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
void logout(vector<Transaction> &transactions, User &currentUser)
{
    Transaction logoutTransaction("endofsession", currentUser); // Create a new logout Transaction
    transactions.push_back(logoutTransaction);                  // Add the logout Transaction to the vector

    cout << "Writing to Daily Transaction File...\n";

    // TO-DO::
    // Make sure the END line from previous write is deleted
    

    // Write to the DailyTransactions file
    ofstream dailyTransactionFile;
    dailyTransactionFile.open("DailyTransactions.txt", ios::app);
    for (int i = 0; i < transactions.size(); i++)
    {
        if (transactions[i].name != "terminated")
        {
            dailyTransactionFile << transactions[i].toString(transactions[i]) << "\n";

            if (transactions[i].name == "sell")
            {
                // TO-DO::
                //
                // Write the game object to AvailableGames under the proper formatting.
            }
        }
    }
    dailyTransactionFile << "END";
    dailyTransactionFile.close();

    cout << "Thank you for using Vapour.\nGoodbye.";

    exit(0);
};

/// <summary>
///
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction createUser(User &currentUser) // Transaction code: 1
{

    // TO-DO::
    // Ensure username cannot be "logout" or "exit"

    string newUsername;
    bool nameBool = true;
    string newUserType;
    bool typeBool = true;
    string whitespace;
    int whitespaceLength;

    cout << "Creating new user. Please input their username:\n";
    // Username input check
    while (nameBool)
    {
        cin >> newUsername;
        if (isValidUser(newUsername))
        {
            cout << "Error! User already exists, please try again:\n";
        }
        else if (newUsername.length() > 25)
        {
            cout << "Error! Username is longer than 15 characters, please enter a shorter name:\n";
        }
        else
        {
            nameBool = false;
        }
    }

    // Usertype input check
    cout << "Username accepted! What type of user are they? (AA,FS,SS,BS): \n";
    while (typeBool)
    {
        cin >> newUserType;
        cout << newUserType << "\n";

        for (int j = 0; j < 2; j++)
        {
            newUserType[j] = toupper(newUserType[j]);
        };

        if (newUserType == "AA")
        {
            typeBool = false;
        }
        else if (newUserType == "FS")
        {
            typeBool = false;
        }
        else if (newUserType == "SS")
        {
            typeBool = false;
        }
        else if (newUserType == "BS")
        {
            typeBool = false;
        }
        else if (newUserType.length() > 2)
        {
            cout << "Error! Type can only be AA, FS, SS, BS. Please try again: \n";
        }
        else
        {
            cout << "Error! Type does not exit. Acceptable types are AA,FS,SS,BS. Please try again: \n";
        }
    }

    // whitespace padding for account name
    for (int i = 0; i < (16 - newUsername.length()); i++)
    {
        whitespace += ' ';
    }

    // read from accounts and throw into text;
    string account;
    ofstream textFile;
    textFile.open("temp.txt");
    ifstream accountsFile;
    accountsFile.open("CurrentUserAccounts.txt");
    while (getline(accountsFile, account))
    {
        if (account != "END")
        {
            textFile << account << "\n";
        }
    }

    // add new account to text;
    textFile << newUsername + whitespace + newUserType + " 000000000";
    textFile << "\nEND";
    remove("CurrentUserAccounts.txt");
    rename("temp.txt", "CurrentUserAccounts.txt");
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
Transaction deleteUser(User& currentUser) // Transaction code: 2
{
    bool isValidInput = false;
    string userInput;
    cout << "Please enter the name of the user you want to delete: ";
    while (!isValidInput)
    {
        cin >> userInput;
        if (currentUser.name == userInput)
        {
            cout << "Error! You can't delete the current user.";
        }
        else if (!isValidUser(userInput))
        {
            cout << "Error! " + userInput + " is not a valid username.";
        }
        else
        {
            isValidInput = true;
        }
        if (!isValidInput)
        {
            cout << "\nPlease enter the name of a valid user to delete: ";
        }
    }

    cout << "\nTest: User to delete should be: " << userInput << "\n";

    string line;
    ifstream usersFile;
    usersFile.open("CurrentUserAccounts.txt");
    ofstream temp("temp.txt");
    while (getline(usersFile, line))
    {
        if (line.substr(0, userInput.length()) != userInput)
        {
            temp << line << endl;
        }
    }

    usersFile.close();
    temp.close();

    remove("CurrentUserAccounts.txt");
    rename("temp.txt", "CurrentUserAccounts.txt");

    ifstream gamesFile;
    gamesFile.open("GameCollection.txt");
    ofstream temp2("temp.txt");
    while (getline(gamesFile, line))
    {
        if (line != "END")
        {
            
            if (line.substr(26, userInput.length()) != userInput)
            {
                temp2 << line << endl;
                //cout << "Writing the following to temp file: " << line << endl;
            }
            else
            {
                //cout << userInput << " should be deleted\n";
            }
        }
    }

    // Close both files
    gamesFile.close();
    temp2.close();

    // Remove GameCollection and replace it with the tempfile with specific user-deletions.
    remove("GameCollection.txt");
    rename("temp.txt", "GameCollection.txt");

    cout << "Success! Games for sale on this account have been cancelled." << endl;

    Transaction deleteUserTransaction("delete", currentUser);
    return deleteUserTransaction;
};

/// <summary>
/// Handles buy transaction.
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction buyGame(User &currentUser) // Transaction code: 3
{
    string gameName, seller, log;
    bool validGame = true;
    bool validSeller = false;

    cout << "Please enter the name of the game you would like to buy: ";
    std::cin.clear();
    std::cin.ignore(100, '\n');
    do {
        
        std::getline(std::cin, gameName);
       
        // Check if gameName is in GameCollection.txt
        validGame = isValidGame(gameName);
        if (!validGame) {
            cout << gameName + " is not available. Please enter another game to purchase: ";
        }

        // Check if the current user has the game in their collection
        else if (isInCollection(gameName, currentUser)) {
            validGame = false;
            cout << "Error: " + gameName + " is already in your collection. Please choose another game to purchase: ";
        }

        // Check if the current user has sufficient funds to buy the game
        else if (!isUserBalanceSufficient(currentUser.name, getGamePrice(gameName))) {
            validGame = false;
            cout << "Error: Do not have sufficient credit to buy " << gameName << ". Please choose another game to purchase: ";
        }

        // Check if current user is the seller of the game
        else if (getSellerForGame(gameName) == currentUser.name) {
            validGame = false;
            cout << "Error: Cannot buy your own game.  Please choose another game to purchase: ";
        }

    } while (!validGame);

    while (!validSeller)
    {
        cout << "Please enter the seller of " + gameName + ": ";
        cin >> seller;

        string storedSeller = getSellerForGame(gameName);

        // Check if the correct seller is input
        if (storedSeller == seller) {
            validSeller = true;
        }
        else {
            cout << "seller input: " << seller << " storedSeller: " << storedSeller << endl;
            cout << "Invalid seller. ";
        }
    }

    double buyerBalance = currentUser.credit - stod(getGamePrice(gameName));
    double sellerBalance = getUserBalance(seller) + stod(getGamePrice(gameName));
    // Update user balances for buyer and seller
    updateUserBalance(currentUser.name, buyerBalance);
    updateUserBalance(seller, sellerBalance);

    // Add purchase to GameCollection.txt
    logGameCollection(gameName, currentUser.name);
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
Transaction sellGame(User &currentUser) // Transaction code: 4
{
    string gameName; // Temporary string to store the name of the game
    float gamePrice; // Better as an int, then parse and validate input.
    string priceString;
    string priceString_whole;
    string priceString_decimals;
    bool nameBool;
    bool priceBool = true;
    bool isFloat, priceInLimit;
    float price;
    // If they don't enter a decimal, we append 00 before storing
    cout << "Creating new listing. Enter the game's title: ";
    // TO-DO:: Input validation
    // Game name max of 25 characters
    // Check AvailableGames file -> Must be a unique Name
    //
    // No further transactions can be accepted on the new game until the next session
    //
    //  One option: Tag game as not for sale: at end of availablegamesfile
    //              -> check for that tag in the buygame() function
    //              -> Logging out removes all tags from the availablegamesfile
    //
    //
    //

    // Check if unique, under 25 characters, not login or logout

    // Read through AvailableGames.txt and ensure unique
    bool validGameName;
    std::cin.clear();
    std::cin.ignore(100, '\n');
    do
    {
        cin.clear();
        getline(cin, gameName);
        bool unique = !inStore(gameName);
        bool length = (gameName.length() <= 25);
        bool notCommand = (gameName != "login" && gameName != "logout");
        if (!unique)
        {
            cout << "Error! Game name has already taken, please try again: ";
            validGameName = false;
        }
        // Check the length of the name
        else if (!length)
        {
            cout << "Error! Game name is longer than 25 characters, please enter a shorter name: ";
            validGameName = false;
        }
        // Ensure it is not login or logout
        else if (!notCommand)
        {
            cout << "Error: can not use those commands at this time. Please enter the game name: ";
            validGameName = false;
        }

        if ((unique == true) && (length == true) && (notCommand == true))
        {
            validGameName = true;
        }
    } while (!validGameName);

    cout << "Enter the game's price: ";
    std::cin.clear();

    // Can get rid of this while loop
    while (priceBool)
    {
        // TO-DO:: Input validation
        // while loop -> iterate until valid
        // Price Max: $999.99, Min: 0.
        // formatting
        while (!isFloat)
        {
            getline(std::cin, priceString);
            // cin >> priceString;
            // cout << "priceString: |" << priceString << "|" << endl;

            istringstream iss(priceString);
            try
            {
                // Check if input string can be converted to a float
                if (iss >> price)
                {
                    char remainingChar;
                    // Check if beginning of the string has numbers but has other characters after
                    if (iss >> remainingChar)
                    {
                        cerr << "Error! Input must be a number. (e.g. 10, 10.00, 1.0): ";
                    }
                    // Check if price amount is within the limits
                    else if (price < 0 || price > 999.99)
                    {
                        std::cerr << "Error! Price must be between 0 and 999.99: ";
                    }
                    else
                    {
                        isFloat = true;
                    }
                }
                else
                {
                    cout << "Error! Input must be a number. (e.g. 10, 10.00, 1.0): ";
                }
            }
            catch (const std::invalid_argument &e)
            {
                cerr << e.what() << std::endl;
            }
        }

        cout << "Entered price: " << price << endl;
        break;
        // Can convert to float
        // if (stof(priceString)) {
        //     cout << "Returns float of: " << stof(priceString) << endl;
        // }
        // // Can't convert to float
        // else {
        //     cout << "Can't convert to float" << endl;
        // }

        // check if input has letters
        // string::size_type pos = priceString.find('.');
        // if (regex_match(priceString, regex(R"((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))")))
        // {
        //     cout << "Reached point 1" << endl;
        //     if (pos != string::npos)
        //     {
        //         priceString_whole = priceString.substr(0, pos);
        //         priceString_decimals = priceString.substr(priceString_whole.length(), 10);
        //         cout << "Reached point 2" << endl;
        //     }
        //     else
        //     {
        //         priceString_whole = priceString;
        //         float priceNoDec = 0.0 + stof(priceString_whole);
        //         cout << priceNoDec << endl;
        //         cout << "Reached point 3" << endl;
        //     }

        //     gamePrice = stof(priceString_whole) + stof(priceString_decimals);
        //     priceBool = false;
        //     cout << "Reached point 4" << endl;
        // }
        // else
        // {
        //     cout << "Error! Input must be a number. (e.g. 10, 10.00, 1.0) \n";
        //     cout << "Reached point 5" << endl;
        // }
        // check if input is greater than 999.99
        // check if input has more than 2 decimal points
    }


    Game gameToSell(currentUser, gameName, gamePrice);

    /*
    *   The below must be moved to logout()
    *
    *
    ofstream availableGamesFile;
    availableGamesFile.open("AvailableGames.txt", ios::app);

    // TO-DO:: The below will not delete the "END" from the last file write
    availableGamesFile << "\n" + gameToSell.toString(); // Should do a replace(sellGame.toString(sellGame), "END");
    availableGamesFile << "\nEND";
    availableGamesFile.close();
    */

    // Need to pass a game to our transaction V
    Transaction sellGameTransaction("sell", currentUser, gameToSell);
    return sellGameTransaction;
};
/// <summary>
///
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction refundGame(User &currentUser) // Transaction code: 5
{
    bool proceedFlag, validBuyer;
    // Validate buyer account
    string buyer = getValidUsernameInput("Please enter the buyer's username (the recipient of the refund): ");
    User buyerUser;
    User sellerUser;
    Game soldGame;
    //User buyerUser = User(buyer, getUserType(buyer), getUserBalance(buyer));  // This is never used...

    // Validate seller account
    string seller = getValidUsernameInput("Please enter the seller's username: ");

    // Validate game and game price
    string game = getValidGameName(buyer, seller);
    string amount = getValidRefundAmount(game);

    // Check if user needs to be warned about reaching the maximum balance possible (999 999)
    if (shouldWarnUserBalance(buyer, amount)) {
        proceedFlag = shouldProceed();
        if (!proceedFlag) {
            cout << "Terminating refund transaction..." << endl;
            return Transaction("terminated", currentUser);
        }
    }

    // Check if seller has sufficient credits to refund buyer
    if (isUserBalanceSufficient(seller, amount)) {
        removeGame(buyer, game);

        double buyerBalance = getUserBalance(buyer) + stod(amount);
        // Ensure balance does not exceed maximum
        if (buyerBalance > 999999.99) {
            buyerBalance = 999999.99;
        }
        double sellerBalance = getUserBalance(seller) - stod(amount);

        // Update buyer and seller balance
        updateUserBalance(buyer, buyerBalance);
        updateUserBalance(seller, sellerBalance);

        // Update Seller/Buyer objects to represent their new balance
        User sellerUser = User(seller, getUserType(seller), getUserBalance(seller));
        buyerUser = User(buyer, getUserType(buyer), getUserBalance(buyer));
        soldGame = Game(sellerUser, game, stof(amount));
    }
    else {
        cout << "Error: Seller does not have the necessary amount of available credits to fully refund the purchase." << endl;
        cout << "Terminating refund transaction." << endl;
    }

    Transaction refundGameTransaction("refund", currentUser, soldGame, buyerUser);
    return refundGameTransaction;
};
// TO-DO:: Implement initial credit as a parameter?

/// <summary>
///
/// </summary>
/// <param name="currentUser">A reference to the User object representing logged in User</param>
/// <returns>A Transaction object, to record each Transaction a user performed while logged in</returns>
Transaction addCredit(User &currentUser) // Transaction code: 6
{
    bool validAcc = true;
    string username, amount, userType, log;
    //ostringstream oss;
    if (currentUser.type == "AA")
    {
        do {
            cout << "Which user would you like to add credit to? ";
            cin >> username;
            validAcc = isValidUser(username);
        } while (!validAcc);
        
        cout << "How much credit would you like to add to " + username + "'s account?";
        
        // TO-DO::
        //  Ensure that no more than $1000 is added to a user's accounbt in one session
        //
        //  Separate function for validation

        cin >> amount;

        userType = currentUser.type;
    }
    else
    {
        username = currentUser.name;
        cout << "How much credit would you like to add to your account?" << endl;
        
        // Validation here too

        cin >> amount;
        userType = getUserType(username);
    }
    // TO-DO:: Check if the userBalance will exceed 999 999 and if so, print out warning
    double userBalance = getUserBalance(username) + stod(amount);
    updateUserBalance(username, userBalance);
    Transaction addCreditTransaction("addcredit", currentUser);
    return addCreditTransaction;
};

/// <summary>
/// Prints the list of users and their information in the system
/// </summary>
void listUsers()
{
    ifstream accountsFile("CurrentUserAccounts.txt");
    string accounts;
    cout << "\nUsername    | Type | Balance\n";
    cout << "============================\n";
    while (getline(accountsFile, accounts))
    {
        cout << accounts << "\n";
    }
};

/// <summary>
/// Prints the list of games and their information in the system
/// </summary>
void listGames()
{
    ifstream gamesFile("AvailableGames.txt");
    string games;
    cout << "\nGame Name                | Seller         | Price\n";
    cout << "=================================================\n";
    while (getline(gamesFile, games))
    {
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
void inputLogic(string transactionName, User &currentUser, vector<Transaction> &dailyTransactions)
{
    string messageString = "";

    // Iterate over the input character array to change each to lowercase.
    for (int i = 0; i < transactionName.length(); i++)
        transactionName[i] = tolower(transactionName[i]); // tolower() sets input to lowercase

    // Valid user types: AA FS, BS, SS (admin, fullstandard, buystandard, sellstandard)

    if (transactionName == "list")
    {
        listGames();
    } // All users can list games
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

    else
    {
        messageString = transactionName + " is not a valid transaction.\n";
    }

    messageString += "Input another transaction: ";
    cout << messageString;
    cin >> transactionName;
    inputLogic(transactionName, currentUser, dailyTransactions); // Recur until Logout()
};

int main()
{
    // TO-DO::
    // Implement the useless "login" transaction that's listed in the requirements

    string userInput;                      // Holds the text a user will input while logging into the system.
    vector<Transaction> dailyTransactions; // Stores the transactions performed by a user while logged in

    // Prompt for username to log in.
    cout << "Welcome to Vapour!\nPlease enter your Username to log in: ";
    cin >> userInput;
    if (userInput == "exit")
    {
        return 0;
    }


    // Wait for valid input before proceding
    while (!isValidUser(userInput))
    {
        cout << userInput + " is not a valid username.\nPlease enter a valid username: ";
        cin >> userInput;
        if (userInput == "exit")
        {
            return 0;
        }
    }

    // TO-DO:: Read AvailableGames File


    // Create a User object with the provided, valid input, and corresponding user data.
    User currentUser = User(userInput, getUserType(userInput), getUserBalance(userInput));

    // The user is now logged in. Prompt to enter a transaction.
    cout << "Welcome " + currentUser.name + "! Please enter a transaction: ";
    cin >> userInput;

    // The user can now enter transaction codes and complete transactions
    inputLogic(userInput, currentUser, dailyTransactions);

    return 0;
}