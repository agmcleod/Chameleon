#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
class Room
{
public:
	Room(std::string name):m_name(name){}
	
	// returns the description of the room
	std::string GetDescription(); 
	
	// returns the name of the room
	std::string GetName();

	void SetDescription(std::string description) { m_description = description; }

	// sets an exit for the room
	void SetExit(std::string direction, Room* neighbour);
	
	// gets the exits of the specified room
	std::map<const std::string, Room*> GetExits();
	
	// prints the description and exits of the room
	void PrintRoomInfo();
	
	void AddEnemy(Enemy& e);
	void RemoveEnemy(Enemy& e);
	// prints the exits
	void PrintExits();
	std::string OutputEnemies();
	void CheckForBattle(Player* p);
	void FightARound(Enemy* e, Player* p);
	void StartTheFight(Player* p);
private:
	std::string m_description;
	std::string m_name;
	std::map<const std::string, Room*> m_exits;
	std::vector<Enemy*> m_enemies;	
};

#endif