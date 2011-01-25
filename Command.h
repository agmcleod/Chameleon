#ifndef COMMAND_H
#define COMMAND_H

#include "Player.h"
#include "Room.h"
#include <iostream>

class Command 
{
public:
	virtual void DoCommand(const Game::arguments& args) = 0;
};
class Go : public Command 
{
public:
	Go(Game* const game):g(*game) {}
	virtual void DoCommand(const Game::arguments& args) 
	{
		if(args.size() == 0)
		{
			std::cout << "Please provide an exit with the go command.\n";
		}
		else
		{
			std::string exitToTake = args[0];
			Room* currentRoom = g.GetCurrentRoom();
			std::map<const std::string, Room*> exits = currentRoom->GetExits();
			std::map<const std::string, Room*>::iterator itr;
			bool goSuccessful = false;
			for(itr = exits.begin(); itr != exits.end(); itr++)
			{
				std::pair<const std::string, Room*> roomExit = *itr;
				if(exitToTake == roomExit.first)
				{
					currentRoom = roomExit.second;
					currentRoom->PrintRoomInfo();
					currentRoom->CheckForBattle(g.GetPlayer());
					g.SetCurrentRoom(*currentRoom);
					goSuccessful = true;
				}
			}
			if(!goSuccessful)
			{
				std::cout << "This room does not have an exit named: " << exitToTake << "\n";
				std::cout << "Type the exits command to see what exits are available\n";
			}
		}
	}
protected:
	Game& g;
};

class Help : public Command
{
public:
	Help(Game* const game):g(*game) {}
	virtual void DoCommand(const Game::arguments& args) 
	{
		std::cout	<< "Help - Commands: \n"
					<< "Go <exit> \n"
					<< "Exits - Prints all the current available exits\n"
					<< "Save <name> - saves the game as a filename with the option specified.\n"
					<< "     If no name specified, will be called chameleon\n"
					<< "Quit - simply quits the game. Be sure to call save ahead of time.\n";

	}
protected:
	Game& g;
};

class Quit : public Command
{
public:
	Quit(Game* const game):g(*game) {}
	virtual void DoCommand(const Game::arguments& args) 
	{
		std::cout << "Thanks for playing!\n";
		exit(1);
	}
protected:
	Game& g;
};
class Exits : public Command
{
public:
	Exits(Game* const game):g(*game) {}
	virtual void DoCommand(const Game::arguments& args) 
	{
		Room* currentRoom = g.GetCurrentRoom();
		std::cout << "Exits for room: " << currentRoom->GetName() << "\n";
		currentRoom->PrintExits();
	}
protected:
	Game& g;
};

class Save : public Command
{
public:
	Save(Game* const game):g(*game) {}
	virtual void DoCommand(const Game::arguments& args) 
	{		
	}
protected:
	Game& g;
};
#endif