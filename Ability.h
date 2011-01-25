#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Ability 
{
public:
	Ability(std::string name, std::string description, double damage, int cost, int endurance_return = 0):m_name(name), m_description(description),
		m_damage(damage), m_cost(cost), m_endurance_return(endurance_return)
	{
	}

	std::string GetName();
	std::string GetDescription();
	double GetDamage();
	int GetCost();
	int GetEnduranceReturn();
private:
	std::string m_name;
	std::string m_description;
	double m_damage;
	int m_cost;
	int m_endurance_return;
};
#endif