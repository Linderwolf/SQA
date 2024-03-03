#ifndef TRANSACTION_H
#define TRANSACTION_H
#endif // !TRANSACTION_H

// The Transaction Class represents an action a user may cause the system to perform
class Transaction
{
	public:
	#pragma region "parameters"
		// Mandatory Parameters
		int code;			// A numeric identifier code for a type of transaction.
		string name;		// The name of a type of transaction
		User user;			// The user performing the transaction	 (includes username, type and credit)

		// Optional Parameters
		Game relevantGame;	// The game being purchased/sold/created (includes gamename, price, and seller's name)
		User otherUser;		// The name of any other user relevant to the transaction, who is not the transacting User.
							// e.g. A User who purchased a game, that the transacting User is refunding.

	#pragma endregion "parameters"

	#pragma region "constructors"

		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a Transaction Code
		/// </summary>
		/// <param name="transactionCode"> : A numeric identifier code for a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		/// <param name="optionalGame"> : The relevant Game, if applicable</param>
		/// <param name="optionalUser"> : A relevant non-acting User, if applicable</param>
		Transaction(int transactionCode, User actingUser, Game optionalGame = Game(), User optionalUser = User()) {
			code = transactionCode;
			name = getTransactionName(transactionCode);
			user = actingUser;
			relevantGame = optionalGame;
			otherUser = optionalUser;
		}

		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a Transaction Name
		/// </summary>
		/// <param name="transactionName"> : The name for a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		/// <param name="optionalGame"> : The relevant Game, if applicable</param>
		/// <param name="optionalUser"> : A relevant non-acting User, if applicable</param>
		Transaction(string transactionName, User actingUser, Game optionalGame = Game(), User optionalUser = User()) {
			code = getTransactionCode(transactionName);
			name = transactionName;
			user = actingUser;
			relevantGame = optionalGame;
			otherUser = optionalUser;
		}

	#pragma endregion "constructors"

	#pragma region "methods"

		/// <summary>
		/// Formats a float value to a 2 decimal place string
		/// </summary>
		/// <param name="floatValue">The floating point number we want as currency</param>
		/// <returns>currencyString: A string formatted to two decimal places.</returns>
		string formatCurrency(float floatValue)
		{
			string currencyString;
			float decimalValue = fmod(floatValue, 1.00);
			// If the value mod 1 is not remainder 0.
			if (decimalValue != 0)
			{
				// It already has a decimal. Set precision to two decimal places.
				currencyString = to_string(decimalValue);
				currencyString.erase(0, currencyString.find_first_of("."));	// Leaves only the decimal value.

				if (currencyString.length() > 3)
				{
					currencyString.erase(3, currencyString.length());	// set to 2 decimal places
				}
				else
				{
					if (currencyString.length() == 1) // Just 1 decimal place.
					currencyString += "0";
				}
				// Attach the 2-decimal places back to the int
				int currencyInt = static_cast<int>(floatValue);
				currencyString = to_string(currencyInt) + "." + currencyString;
				return currencyString;
			}
			else // Otherwise it has no decimal value, or trailing zeros.
			{ 
				currencyString = to_string(floatValue);
				currencyString.erase(currencyString.find_first_of("."), currencyString.length());
				currencyString = to_string(floatValue) + ".00";
				return currencyString;
			}
		}

		/// <summary>
		/// Returns the name of a transaction, given a transaction code
		/// </summary>
		/// <param name="code">A numeric identifier for a transaction</param>
		/// <returns>The corresponding name of that transaction</returns>
		string getTransactionName(int code) {
			if (code == 0) { return "endofsession"; }
			if (code == 1) { return "create"; }
			if (code == 2) { return "delete"; }
			if (code == 3) { return "buy"; }
			if (code == 4) { return "sell"; }
			if (code == 5) { return "refund"; }
			if (code == 6) { return "addcredit"; }
			else { return "Error: Invalid Transaction Code"; } // ERROR - else path should never be reached
		}

		/// <summary>
		/// Returns the code of a transaction, given a transaction name
		/// </summary>
		/// <param name="name">The name of the transaction</param>
		/// <returns>The corresponding numeric identifier for that transaction</returns>
		int getTransactionCode(string transactionName) {
			if (transactionName == "endofsession" || transactionName == "logout")   { return 0; }
			if (transactionName == "create")		 { return 1; }
			if (transactionName == "delete")		 { return 2; }
			if (transactionName == "buy")			 { return 3; }
			if (transactionName == "sell")			 { return 4; }
			if (transactionName == "refund")		 { return 5; }
			if (transactionName == "addcredit")	     { return 6; }
			else { return 99; }	// ERROR, or cancelled transaction
		}

		/// <summary>
		/// Returns a line to add to the DailyTransactions report, depending on the Transaction performed
		/// </summary>
		/// <returns>A string formatted to match the DailyTransaction report schema</returns>
		string toDailyTransactionString(Transaction transaction) {
			//TO-DO:: Double-check that the transaction codes have leading 0s
			
			string formattedString;				//	The final string to return
			string transactionCodeString;		//	The transaction code, formatted into a string
			string transactionCreditString;		//	The transacting User's Credit, formatted into a string
			string transactionUnitPriceString;	//	The relevant Game's Price, formatted into a string

			// Process the Transaction Code
			if (transaction.code < 10) { transactionCodeString = "0" + to_string(transaction.code); }

			// Process the Current User's Credit
			transactionCreditString = to_string(transaction.user.credit);

			// Process the Game's Price
			if (transaction.relevantGame.name != "                   ")
			{
				transactionUnitPriceString = to_string(transaction.relevantGame.price);
			}
			else { transactionUnitPriceString = "Error. Game Object was defaulted..."; }

			// Every line starts with the transaction Code
			formattedString = transactionCodeString + " ";

			// create, delete, add credit, end of session transactions
			if (transaction.code == 1 || transaction.code == 2 || transaction.code == 6 || transaction.code == 0)	
			{
				/*
				 Form: XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
				
				 TO-DO:: Requirements Clarification
				 
				 From the requirements:
				 "'UUUUUUUUUUUUUUU' is the username (buyer if two users in the transaction)"
				 yet delete is a transaction of 2 users without a buyer.
				*/

				formattedString += transaction.user.type + " " + transactionCreditString;
			}
			else if (transaction.code == 03)	// Buy Transaction
			{
				// TO-DO:: Fix this!
				// 
				//Form: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
				// I game name, S seller's username, U buyer's username, P game's price
				//
				//		This assumes the current user to be the buyer.
				formattedString += transaction.relevantGame.name + " " + transaction.relevantGame.seller.name +
					" " + transaction.user.name + " " + to_string(transaction.relevantGame.price);
			}
			else if (transaction.code == 04)	// Sell Transaction
			{
				//Form: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_PPPPPP
				// Game Name, Seller's Name, Price
				formattedString += transaction.relevantGame.name + " " +
					transaction.relevantGame.seller.name + " " + to_string(transaction.relevantGame.price);
			}
			else if (transaction.code == 5)	// refund transaction
			{
				/* UUUUUUUUUUUUUUU is the buyer’s username
				 SSSSSSSSSSSSSSS is the seller’s username

				 TO-DO:: Fix this!

				 This is a privileged transacion
				 Therefore an admin is the current user, crediting a buyer from the seller's account
					our Transaction Object must thus have an optional "Buyer name" parameter, or another alternative

				 and the below code is in error

				Form: XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
				*/

				formattedString += transaction.user.name + " " +
					transaction.relevantGame.seller.name + " " + to_string(transaction.relevantGame.price);
			}
			/*
			*	Requires additional formatting
			*	Requirements below:
			* 
			alphabetic fields are left justified, filled with spaces
			(e.g.Jane_Doe____________ for account holder Jane Doe)
				unused numeric fields are filled with zeros
				(e.g., 0000)
				In a numeric field that is used to represent a monetary value, “.00” is appended to the end of the value
				(e.g. 00110.00 for 110)
				unused alphabetic fields are filled with spaces(blanks)
				(e.g., ________________________)
				the sequence of transactions ends with an end of session(00) transaction code
			*/
			else { formattedString += transaction.name + " Must not have transaction code logic implemented in the Transaction class."; }
			return formattedString;
		}

		/// <summary>
		/// Returns a line to add to the Available Games file.
		/// This assumes the transaction makes use of a game. Validation must thus be done beforehand.
		/// </summary>
		/// <returns>A string formatted to match the Available Games file schema</returns>
		string toAvailableGamesString(Transaction transaction) {
			/*  IIIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_PPPPPP
				26 GameName                15 SellerName   6 Price
			*/
			// Format Constants
			const int GameNameSize = 26;	// The number of characters a game's name may have
			const int SellerNameSize = 15;  // The number of characters a seller's name may have
			const int PriceSize = 6;        // The number of characters a game's Price may have
			
			int stringSize;				// A temporary int to hold the length of strings from the transaction object.

			string formattedString;		// The final string to return
			string gameNameString;		// The GameName to be formatted to 26 characters
			string priceString;			// The Price to be formatted to 6 characters

			// Game Name Formatting
			stringSize = transaction.relevantGame.name.size();
			if (stringSize < GameNameSize)	// the game name is fewer than the desired characters
			{
				// Append the Game Name. Fill the string with spaces (+1 for space between name and price)
				formattedString += transaction.relevantGame.name + string(1 + GameNameSize - min(GameNameSize, stringSize), ' ');
			}
			else
			{
				if (stringSize > GameNameSize)	// The game name is too large
				{
					formattedString += "GameNameSize>ConstantError ";
				}
				else // The game name is the right size
				{
					formattedString += transaction.relevantGame.name + " ";
				}
			}

			// Seller Name Formatting
			stringSize = transaction.user.name.size();
			if (stringSize < SellerNameSize)	// The seller's name is fewer than the desired characters
			{	
				// Process: Append the Seller Name. Fill the string with spaces (+1 for space between name and price)
				formattedString += transaction.user.name + string(1 + SellerNameSize - min(SellerNameSize, stringSize), ' ');
			}
			else
			{
				if (stringSize > SellerNameSize)  // The user name is too large
				{
					formattedString += "NameSize>CError ";
				}
				else  // The user name is the right number of chars
				{
					formattedString += transaction.user.name + " ";
				}
			}

			// Price Formatting
			if (transaction.relevantGame.price > 999.99)	// The game price is too large
			{
				formattedString += "$ERROR";
			}
			else // Format to currency and fill with leading 0s
			{
				priceString = formatCurrency(transaction.relevantGame.price);
				std::cout << "\nAfter format Currency: " + priceString;
				stringSize = priceString.size();	// min doesn't like size_t for some reason, even though it's essentially a x64 int...
				std::cout << "\nPrice String Size: " + stringSize;
				priceString = string(PriceSize - min(PriceSize, stringSize), '0') + priceString;
				formattedString += priceString;
				std::cout << "\nFinal String: " + formattedString;
			}

			return formattedString;
		}

	#pragma endregion "methods"

private:

};