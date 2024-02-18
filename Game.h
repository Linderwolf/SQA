#ifndef GAME_H
#define GAME_H
#endif // !GAME_H
// Or just use "#pragma once"...

// The Game Class represents a Video-Game listed for sale in the system.
class Game
{
	public:
		string gameName;	// The title of a videogame to be sold
		string sellerName;	// The username of the seller of a videogame
		float unitPrice;	// The price the game is to be listed for sale at

		//XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
		// Default Constructor. 
		// If no information is provided, default to appropriate character length for report formatting.
		Game()
		{
			gameName = "                   ";	// 19 characters to match Daily Transaction File
			sellerName = "               ";		// 15 characters to match Daily Transaction File
			unitPrice = 0;
		}
		// Parameterized Constructor
		Game(string name, string userName, float price)
		{
			gameName = name;
			sellerName = userName;
			unitPrice = price;
		}

	private:

};