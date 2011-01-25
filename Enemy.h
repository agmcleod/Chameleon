#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"

#include <string>
class Enemy : public Character
{
public:
	Enemy(float health, std::string name, double skill):Character(health, name), m_skill(skill)
	{
		m_isAlive = true;
	}

	double GetSkillLevel();

private:
	double m_skill;
};

#endif