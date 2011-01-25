#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
class Room;

class Character
{
public:
	Character(double health): m_health(health)
	{
		m_isAlive = true;
	}
	Character(double health, std::string name): m_health(health), m_name(name)
	{
		m_isAlive = true;
	}
	void GiveHealth(double health);
	void RemoveHealth(double health);
	double GetHealth();
	std::string GetName();
	bool IsAlive();
protected:
	double m_health;
	std::string m_name;
	bool m_isAlive;
};

#endif