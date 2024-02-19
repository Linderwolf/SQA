#ifndef GAME_H
#define GAME_H
#endif // !GAME_H
// Or just use "#pragma once"...

// The Game Class represents a Video-Game listed for sale in the system.
class Game
{
	public:
		User seller;	// The User who is listing the game for sale
		string name;	// The title of a videogame to be sold
		// TO-DO:: Make price an int. Parse and validate.
		float price;	// The price the game is to be listed for sale at

		//XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
		// Default Constructor. 
		// If no information is provided, default to appropriate character length for report formatting.
		Game()
		{
			seller = User();	// Default Construcor has a name of 15 character spaces to match Daily Transaction File
			name = "                   ";	// 19 characters to match Daily Transaction File
			price = 0;
		}
		// Parameterized Constructor
		Game(User gameSeller, string gameName, float gamePrice)
		{
			seller = gameSeller;
			name = gameName;
			price = gamePrice;
		}
		
		/// <summary>
		/// Returns a string formatted to fit the AvailableGames.txt schema
		/// </summary>
		/// <param name="newlyListedGame"> : A game object to be listed for sale</param>
		/// <returns>formattedString : A string formatted to fit the AvailableGames.txt format</returns>
		string toString()
		{   //25 chars                   15 chars        $1000.
			//Stardew Valley             sellstandard    000025
			int numberOfSpaces = 0;					// the number of spaces to pad
			int gameNameChars = 25;					// game names have 25 characters
			int sellerNameChars = 15;

			string formattedString = "";		// The string to return in AvailableGames.txt formatting.
			//string gameNameString = name;			// A temporary string to process the game's name
			//string sellerNameString = seller.name;	// A temporary string to process the seller's name

			// String size to large errors here...
			
			if (name.length() < gameNameChars) { numberOfSpaces = name.length() - gameNameChars; }
			formattedString = name + (numberOfSpaces, ' ');
			
			if (seller.name.length() < sellerNameChars) { numberOfSpaces = seller.name.length() - sellerNameChars; }
			formattedString += seller.name + (numberOfSpaces, ' ') + to_string(price);
			
			return formattedString;
		}

	private:

};