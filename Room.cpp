#include "Room.h"

std::string Room::GetDescription()
{
	return m_description;
}

std::string Room::GetName()
{
	return m_name;
}

void Room::SetExit(const std::string direction, Room* neighbour)
{
	m_exits.insert(std::pair<std::string, Room*>(direction, neighbour) );
}

std::map<const std::string, Room*> Room::GetExits()
{
	return m_exits;
}

void Room::PrintRoomInfo()
{
	std::cout << "You are in the room: " << GetName() << "\n";
	std::cout << "Enemies: " << OutputEnemies() << "\n";
	std::cout << "description: " << GetDescription() << "\nExits:\n";
	PrintExits();
}

void Room::PrintExits()
{
	std::map<const std::string, Room*>::iterator it;
	for(it = m_exits.begin(); it != m_exits.end(); it++)
	{
		std::cout << it->first << "\n";		
	}
	std::cout << "\n";
}

void Room::AddEnemy(Enemy& e)
{
	m_enemies.push_back(&e);
}

std::string Room::OutputEnemies()
{
	std::string output = "";
	std::vector<Enemy*>::iterator itr;
	for(itr = m_enemies.begin(); itr != m_enemies.end(); itr++)
	{
		Enemy* e = *itr;
		if(e->IsAlive()) 
		{
			output += e->GetName() + " ";
		}
	}
	return output;
}

void Room::CheckForBattle(Player* p)
{
	if(m_enemies.size() > 0)
	{
		StartTheFight(p);
	}
}

void Room::StartTheFight(Player* p)
{
	std::vector<Enemy*>::iterator itr;
	p->SetAdrenaline(0);
	for(itr = m_enemies.begin(); itr != m_enemies.end(); itr++)
	{
		Enemy* e = *itr;
		if(e->IsAlive())
		{
			std::cout << "Fighting: " << e->GetName() << "\n";
			FightARound(e, p);
		}
	}
	if(p->IsAlive())
	{
		std::cout << "You have " << p->GetHealth() << " health left\n";
	}
}

void Room::FightARound(Enemy* e, Player* p)
{
	bool roundFinished = false;
	while(!roundFinished)
	{
		double damage = e->GetSkillLevel();
		std::cout << e->GetName() << " throws a punch. You take " << damage << " damage\n";
		p->RemoveHealth(damage);
		std::cout << "You have " << p->GetHealth() << " health left\n";
		double playerDamage = p->Attack();
		// remove health from the damage dealt
		// damage is reduced by a percentage of adrenaline. Max 15% reduction
		if(!e->IsAlive())
		{
			std::cout << "You defeated " << e->GetName() << "\n";			
			roundFinished = true;
		}
		else 
		{
			e->RemoveHealth(playerDamage * (p->GetCurrentAdrenaline() / 10));
			if(!p->IsAlive())
			{
				// the main gameloop in Chameleon.cpp tells the player
				// that they have died
				roundFinished = true;
			}
		}
		p->IncreaseAdrenalineLevel(0.3);
		std::cout << e->GetName() << " takes " << playerDamage << " damage\n";		
	}
}