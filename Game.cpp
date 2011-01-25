// game.cpp
#include "Game.h"
#include "Command.h"


namespace GameHelpers 
{
	std::string& ToLower(std::string& stringToConvert)
	{
		for(unsigned int i = 0; i < stringToConvert.length(); i++)
		{
			stringToConvert[i] = tolower(stringToConvert[i]);		
		}
		return stringToConvert;
	}
	
	std::vector<std::string> SplitIntoWords(const std::string& str)
	{
		std::vector<std::string> words;
		// skip spaces at the beginning
		std::string::size_type lastPos = str.find_first_not_of(" ", 0);
		// find first non-space
		std::string::size_type pos = str.find_first_of(" ", lastPos);

		while(std::string::npos != pos || std::string::npos != lastPos)
		{
			// found a word, add it to the vector
			words.push_back(str.substr(lastPos, pos - lastPos));
			// Skip spaces.  
			lastPos = str.find_first_not_of(" ", pos);
			// Find next "non-space"
			pos = str.find_first_of(" ", lastPos);
		}
		return words;
	}
}

std::string Game::FirstWordOf(const std::string& line)
{
	return line.substr(0, line.find(' '));		
}

std::string Game::RestOf(const std::string& line)
{
	std::string::size_type pos = line.find_first_of(" ");	
	if (pos != std::string::npos)
	{
		return line.substr(pos + 1);
	}
	else 
	{
		return "";
	}	
}

Room* Game::GetCurrentRoom()
{
	return currentRoom;
}

void Game::SetCurrentRoom(Room& r)
{
	currentRoom = &r;
}

std::string Game::GetUserInput()
{
	std::cout << "Enter Command\n";
	std::cout << ">> ";
	std::string line = "";
	std::getline(std::cin, GameHelpers::ToLower(line));
	return line;
}

void Game::GenerateEnemies(World& w)
{
	Enemy e = Enemy(10, "Henchman", 5);
	Enemy e2 = Enemy(10, "Henchman", 4);
	Enemy boss = Enemy(25, "Bossman", 10);

	// store all the enemies in a vector
	all_enemies.push_back(e);
	all_enemies.push_back(e2);
	all_enemies.push_back(boss);

	w[1].AddEnemy(all_enemies[0]);
	w[1].AddEnemy(all_enemies[1]);
	w[2].AddEnemy(all_enemies[2]);
}

/**
* This interprets input from the user to see if it matches a command
* if so, the command is called, and any other arguments applied are forwarded to the function
* that deals with the command
*/
void Game::InterpretCommand(argument_mapping& mapping, const std::string& fromUser) 
{
	// grab the first word the user typed, to compare with commands
	std::string firstWord = FirstWordOf(fromUser);
	// grab the rest incase of passed arguments
	std::string commandLine = RestOf(fromUser);
	// convert the string into args
	arguments args = GameHelpers::SplitIntoWords(commandLine);
	argument_mapping::iterator it = mapping.find(firstWord);
	// so long as we're not out of bounds, continue
	if (it != mapping.end()) 
	{
		// using the CommandPtr of the map, call the DoCommand passing the arguments
		((it->second)->DoCommand)(args);				
	} 
}

/** 
* This returns a map that contains the main string required to call a command, 
* and the command object itself. The function returns the map of these functions
*/
Game::argument_mapping Game::GetGameCommands() 
{
	// create the map to return
	argument_mapping commands;
	
	// create a CommandPtr to point to a Go object on the heap
	CommandPtr goCmd = new Go(this);
	// add the command to the map
	commands.insert(std::pair<std::string, CommandPtr>("go", goCmd));
	
	CommandPtr helpCmd = new Help(this);
	commands.insert(std::pair<std::string, CommandPtr>("help", helpCmd));
	
	CommandPtr quitCmd = new Quit(this);
	commands.insert(std::pair<std::string, CommandPtr>("quit", quitCmd));

	CommandPtr exitsCmd = new Exits(this);
	commands.insert(std::pair<std::string, CommandPtr>("exits", exitsCmd));

	CommandPtr saveCmd = new Save(this);
	commands.insert(std::pair<std::string, CommandPtr>("save", saveCmd));
	return commands;
}

void Game::StartGame()
{
	CreateRooms(world);
	currentRoom = &world[0];
	GenerateEnemies(world);
	// make sure the memory is available.
	try 
	{
		m_chameleon = new Player(25);		
	}
	catch(std::bad_alloc&)
	{
		std::cout << "Could not allocate memory to initalize the player\n";
	}
	// print welcome information
	PrintWelcome();
	// print current room info
	currentRoom->PrintRoomInfo();
	// store commands in local map
	commands = GetGameCommands();	
}

void Game::StartANewGame()
{
	delete m_chameleon;
	StartGame();
}

void Game::PlayATurn()
{
	InterpretCommand(commands, GetUserInput());
}

void Game::CreateRooms(World& w)
{
	Room basement("basement");
	Room hallway("hallway");
	Room lounge("lounge");
	Room lobby("lobby");
	Room office("office");
	Room security("security center");

	basement.SetDescription("The basement is quite empty and safe. You hear noise above you.");
	hallway.SetDescription("Like the rest of the building, the hallway has a cold, metallic touch.");
	lounge.SetDescription("In the lounge area, you see a television set and a couple couches.");
	lobby.SetDescription("A big open area, that holds the main entrance doors to the building.");
	office.SetDescription("An office room, documentation of all activities in the city");
	security.SetDescription("One of the many cctv offices and control centres in the building");

	w.push_back(basement);
	w.push_back(hallway);
	w.push_back(lounge);
	w.push_back(lobby);
	w.push_back(office);
	w.push_back(security);
	SetExits(w);
}

void Game::SetExits(World& w)
{
	Room* pBasement = &w[0];
	Room* pHallway = &w[1];
	Room* pLounge = &w[2];
	Room* pLobby = &w[3];
	Room* pOffice = &w[4];
	Room* pSecurity = &w[5];

	pBasement->SetExit("south", pHallway);

	pHallway->SetExit("up", pLounge);
	pHallway->SetExit("north", pBasement);

	pLounge->SetExit("north", pLobby);
	pLounge->SetExit("down", pHallway);

	pLobby->SetExit("west", pOffice);
	pLobby->SetExit("south", pLounge);

	pOffice->SetExit("south", pSecurity);
	pOffice->SetExit("east", pLobby);

	pSecurity->SetExit("north", pOffice);
}

void Game::PrintWelcome()
{
	std::cout << "Welcome to the rpg game called Chameleon!\n" 
		<< "You are a highly trained operative named The Chameleon\n"
		<< "You have snuck into an enemy spire. You are required to \n"
		<< "disable their operational systems\n" 
		<< "and take out their leader.\n\n"
		<< "To get started, and learn the commands, type help\n"
		<< "To move from room to room, use the go command, \n"
		<< "followed by listed exits of your current location.\n"
		<< "You can of course display the current exits, by typing exits.\n\n"
		<< "Be sure to have fun, and when having trouble, type /help\n\n\n";
}

Player* Game::GetPlayer() 
{
	return m_chameleon;
}
