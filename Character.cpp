#include "Character.h"
#include "Room.h"

void Character::GiveHealth(double health)
{
	m_health += health;
}

void Character::RemoveHealth(double health)
{
	m_health -= health;
	if(m_health <= 0)
	{
		m_isAlive = false;
	}
}
double Character::GetHealth()
{
	return m_health;
}

std::string Character::GetName()
{
	return m_name;
}

bool Character::IsAlive()
{
	return m_isAlive;
}