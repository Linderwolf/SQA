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

		/*	Redundant Constructors
		* 
		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a transaction name, and the current user.
		/// </summary>
		/// <param name="transactionName"> : The name of a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		Transaction(string transactionName, User actingUser) {
			code = getTransactionCode(transactionName);
			name = transactionName;
			user = actingUser;
		}

		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a transaction code, and the current user.
		/// </summary>
		/// <param name="transactionCode"> : A numeric identifier code for a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		Transaction(int transactionCode, User actingUser) {
			code = transactionCode;
			name = getTransactionName(transactionCode);
			user = actingUser;
		}

		
		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a transaction code, game, and no other user (Buy)
		/// </summary>
		/// <param name="transactionCode"> : A numeric identifier code for a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		/// <param name="optionalGame"> : The relevant Game, if applicable</param>
		Transaction(int transactionCode, User actingUser, Game optionalGame = Game()) {
			code = transactionCode;
			name = getTransactionName(transactionCode);
			user = actingUser;
			relevantGame = optionalGame;
		}

		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a transaction name, game, and no other user (Buy)
		/// </summary>
		/// <param name="transactionName"> : The name of a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		/// <param name="optionalGame"> : The relevant Game, if applicable</param>
		Transaction(string transactionName, User actingUser, Game optionalGame = Game()) {
			code = getTransactionCode(transactionName);
			name = transactionName;
			user = actingUser;
			relevantGame = optionalGame;
		}
		*/

		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a transaction code, two users and no games.
		/// </summary>
		/// <param name="transactionCode"> : A numeric identifier code for a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		/// <param name="optionalUser"> : A relevant non-acting User, if applicable</param>
		Transaction(int transactionCode, User actingUser, User optionalUser = User()) {
			code = transactionCode;
			name = getTransactionName(transactionCode);
			user = actingUser;
			otherUser = optionalUser;
		}

		/// <summary>
		/// Parameterized Constructor of a Transaction Object, given a transaction name, two users and no games.
		/// </summary>
		/// <param name="transactionName"> : The name of a type of transaction.</param>
		/// <param name="actingUser"> : The User performing the transaction</param>
		/// <param name="optionalUser"> : A relevant non-acting User, if applicable</param>
		Transaction(string transactionName, User actingUser, User optionalUser = User()) {
			code = getTransactionCode(transactionName);
			name = transactionName;
			user = actingUser;
			otherUser = optionalUser;
		}
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
				currencyString = to_string(currencyInt) + currencyString;
				return currencyString;
			}
			else // Otherwise it has no decimal value, or trailing zeros.
			{ 
				currencyString = to_string(floatValue);
				// Delete trailing zeros
				while (currencyString.back() == '0') { currencyString.pop_back(); }
				currencyString += "00";
				return currencyString;
			}
		}

		/// <summary>
		/// Pads a string with leading zeros
		/// </summary>
		/// <param name="desiredNumberOfCharacters">The number of characters the string is to be formatted to</param>
		/// <param name="stringToPad">The string to be formatted</param>
		/// <returns>A string formatted to the desired amount of characters, with leading zeros</returns>
		string formatLeadingZeros(int desiredNumberOfCharacters, string stringToPad)
		{
			int stringSize = stringToPad.size();	// min doesn't like size_t for some reason, even though it's essentially a x64 int...
			string zeros = "";
			if (stringSize < desiredNumberOfCharacters)
			{
				zeros = string(desiredNumberOfCharacters - std::min(desiredNumberOfCharacters, stringSize), '0');
			}
			else { return stringToPad; }	// String is already at least equal in length to desired number of characters
			return zeros + stringToPad;
		}

		/// <summary>
		/// Pads a string with trailing spaces
		/// </summary>
		/// <param name="desiredNumberOfCharacters">The number of characters the string is to be formatted to</param>
		/// <param name="stringToPad">The string to be formatted</param>
		/// <param name="extraSpace">Whether to add an additional space, for </param>
		/// <returns>A string formatted to the desired amount of characters, with trailing spaces</returns>
		string formatTrailingSpaces(int desiredNumberOfCharacters, string stringToPad, bool extraSpace = false)
		{
			int stringSize = stringToPad.size();// The size of the string to pad.
			string formattedString = "";		// The formatted string  to return
			if ( stringSize < desiredNumberOfCharacters)	// the game name is fewer than the desired characters
			{
				// Append the Game Name. Fill the string with spaces.
				formattedString += stringToPad + string(extraSpace + desiredNumberOfCharacters - min(desiredNumberOfCharacters, stringSize), ' ');
			}
			return formattedString;
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
			/*
			*	Formatting Requirements:
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
			string formattedString;				//	The final string to return
			string transactionCodeString;		//	The transaction code, formatted into a string
			
			// Process the Transaction Code to 2 digits
			if (transaction.code < 10) { transactionCodeString = "0" + to_string(transaction.code); }

			// Every line starts with the transaction Code
			formattedString = transactionCodeString + " ";

			// Formatting is then dependent on Transaction Type as follows::
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

				// Flags
				bool loggedInUserFlag = true;	// Whether the currently logged in user is the one to be recorded in the Daily Transactions File

				const int UserNameSize = 15;
				const int UserCreditSize = 9;

				// The below strings are to minimize code redundancy. 
				//   -> Check if a flag is true
				//   -> Change the user they reference based on the flag.
				string userNameString;			// Temporary string to hold a username		
				string userTypeString;			// Temporary string to hold the usertype
				string transactionCreditString; // Temporary string to hold the user's credit.

				if (transaction.code == 1)	// Create
				{
					// Use the created User's information
					loggedInUserFlag = false;
				}
				if (transaction.code == 2)
				{
					// Use the deleted User's information
					loggedInUserFlag = false;
				}
				if (transaction.code == 6)
				{
					if (transaction.user.type == "AA")	// Admin
					{
						// They're adding credit to another user
						loggedInUserFlag = false;
					}
					else
					{
						// Use the current user's information
						loggedInUserFlag = true;
					}
				}
				// If none of the above, it's a logout/endofsession transaction. 
				// Current user remains the user to report on.
				if (loggedInUserFlag)
				{
					userNameString = transaction.user.name;
					userTypeString = transaction.user.type + " ";
					transactionCreditString = formatCurrency(transaction.user.credit);
				}
				else
				{
					userNameString = transaction.otherUser.name;
					userTypeString = transaction.otherUser.type + " ";
					transactionCreditString = formatCurrency(transaction.otherUser.credit);
				}

				formattedString += formatTrailingSpaces(UserNameSize, userNameString, true) +
					userTypeString + formatLeadingZeros(UserCreditSize, transactionCreditString);
			}
			else
			{
				if (transaction.code == 3)	// Buy Transaction
				{
					const int GameNameSize = 19;
					const int SellerNameSize = 15;
					const int BuyerNameSize = 14;
					const int PriceSize = 6;

					int stringSize;
					string gameName = formatTrailingSpaces(GameNameSize, transaction.relevantGame.name, true);
					string sellerName = formatTrailingSpaces(SellerNameSize, transaction.relevantGame.seller.name, true);
					string buyerName = formatTrailingSpaces(BuyerNameSize, transaction.user.name, true);
					string price = formatLeadingZeros(PriceSize, formatCurrency(transaction.relevantGame.price));

					//Form: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
					// I game name 19, S seller's username 15, U buyer's username 14, P game's price
					//
					//		This assumes the current user to be the buyer.

					formattedString += gameName + sellerName + buyerName + price;
				}
				if (transaction.code == 4)	// Sell Transaction
				{
					const int GameNameSize = 19;
					const int SellerNameSize = 13;
					const int PriceSize = 6;
					//Form: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_PPPPPP
					// Game Name, Seller's Name, Price
					formattedString += formatTrailingSpaces(GameNameSize, transaction.relevantGame.name, true) +
						formatTrailingSpaces(SellerNameSize, transaction.relevantGame.seller.name, true) +
						formatLeadingZeros(PriceSize, formatCurrency(transaction.relevantGame.price));
				}
				if (transaction.code == 5)	// refund transaction
				{
					const int BuyerNameSize = 15;
					const int SellerNameSize = 15;
					const int CreditSize = 9;

					/*
					  Form: XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
					  UUUUUUUUUUUUUUU is the buyer’s username
					  SSSSSSSSSSSSSSS is the seller’s username

					 This is a privileged transacion
					 Therefore an admin is the current user, crediting a buyer from the seller's account
						our Transaction Object must thus have an optional otherUser parameter for the buyer.
						The seller can be referenced by the Game object.
					*/

					formattedString += formatTrailingSpaces(BuyerNameSize, transaction.otherUser.name, true) +
						formatTrailingSpaces(SellerNameSize, transaction.relevantGame.seller.name, true) +
						formatLeadingZeros(CreditSize, formatCurrency(transaction.relevantGame.price));
				}
			}
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
			
			priceString = formatCurrency(transaction.relevantGame.price);
		
			formattedString += formatLeadingZeros(PriceSize, priceString);

			return formattedString;
		}

	#pragma endregion "methods"

private:

};