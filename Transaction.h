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
			if (transactionName == "endofsession")   { return 0; }
			if (transactionName == "create")		 { return 1; }
			if (transactionName == "delete")		 { return 2; }
			if (transactionName == "buy")			 { return 3; }
			if (transactionName == "sell")			 { return 4; }
			if (transactionName == "refund")		 { return 5; }
			if (transactionName == "addcredit")	     { return 6; }
			else { return 99; }	// ERROR - else path should never be reached
		}

		/// <summary>
		/// Returns a line to add to the DailyTransactions report, depending on the Transaction performed
		/// </summary>
		/// <returns>A string formatted to match the DailyTransaction report schema</returns>
		string ToString(Transaction transaction) {
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
			if (transaction.relevantGame.gameName != "                   ")
			{
				transactionUnitPriceString = to_string(transaction.relevantGame.unitPrice);
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
			else if (transaction.code == 03)	// Sell Transaction
			{
				//Form: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_PPPPPP
				// Game Name, Seller's Name, Price
				formattedString += transaction.relevantGame.gameName + " " +
					transaction.relevantGame.sellerName + " " + to_string(transaction.relevantGame.unitPrice);
			}
			else if (transaction.code == 04)	// Buy Transaction
			{
				// TO-DO:: Fix this!
				// 
				//Form: XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
				// I game name, S seller's username, U buyer's username, P game's price
				//
				//		This assumes the current user to be the buyer.
				formattedString += transaction.relevantGame.gameName + " " + transaction.relevantGame.sellerName + 
					" " + transaction.user.name + " " + to_string(transaction.relevantGame.unitPrice);
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
					transaction.relevantGame.sellerName + " " + to_string(transaction.relevantGame.unitPrice);
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

	#pragma endregion "methods"

private:

};