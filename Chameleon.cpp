// Chameleon.cpp : Defines the entry point for the console application.
//

#include "Game.h"
#include <iostream>

int main()
{
	bool playing = true;
	Game g;
	g.StartGame();
	do
	{
		g.PlayATurn();
		if(!g.GetPlayer()->IsAlive())
		{
			std::string in = "";
			do
			{
				std::cout << "Oh no, you died! Play again?y/n";
				std::getline(std::cin, in);
			}while(in != "Y" && in != "y" && in != "N" && in != "n");
			if(in == "y" || in == "Y") 
			{
				g.StartANewGame();
			}
			else 
			{
				playing = false;
			}
		}
	}while(playing);
	return 0;
}

