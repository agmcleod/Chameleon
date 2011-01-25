#include "Ability.h"

std::string Ability::GetName()
{
	return m_name;
}
std::string Ability::GetDescription()
{
	return m_description;
}
double Ability::GetDamage()
{
	return m_damage;
}
int Ability::GetCost()
{
	return m_cost;
}

int Ability::GetEnduranceReturn()
{
	return m_endurance_return;
}