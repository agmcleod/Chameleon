#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Room.h"
#include <string>
#include <vector>
#include <map>

class Command;
namespace GameHelpers 
{
	std::string& ToLower(std::string& stringToConvert);	
	std::vector<std::string> SplitIntoWords(const std::string& str);
}


class Game
{
public:
	Game()
	{		
	}
	~Game()
	{
		delete m_chameleon;
	}
	typedef std::vector<Room> World;

	// Creates all the rooms appropriately 
	void CreateRooms(Game::World& w);

	// Adds all the exits to the rooms
	void SetExits(Game::World& w);	
	
	// prints starting messages for the game
	// gives basic instructions
	void PrintWelcome();
	
	// has all the initialization code of the game it self
	void StartGame();

	void StartANewGame();

	void PlayATurn();

	Player* GetPlayer();
	Room* GetCurrentRoom();
	void SetCurrentRoom(Room& r);

	// fills the vector with enemies
	void GenerateEnemies(World& w);

	/***** functions and types for working with the commands *****/

	// establish an arguments type that can store valid command args
	typedef std::vector<std::string> arguments;
	// overload the operator () to call a command given arguments
	typedef void (*action)(const arguments&);

	// define a pointer to type Command
	typedef Command* CommandPtr;

	// argument mappings for attaching a string to call a function
	typedef std::map<std::string, CommandPtr> argument_mapping;

	std::string FirstWordOf(const std::string& line);
	std::string RestOf(const std::string& line);
	argument_mapping GetGameCommands();
	void InterpretCommand(argument_mapping& mapping, const std::string& from_user); 
	std::string GetUserInput();
	
private:
	Player* m_chameleon;
	Room* currentRoom;
	World world;
	argument_mapping commands;
	std::vector<Enemy> all_enemies;
};
#endif
