#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "Ability.h"
#include <iostream>
#include <vector>

class Player : public Character
{
public:
	// player is given health amount, and a starting location
	Player(double health, double adrenaline = 0, int endurance = 25, const double max_adren = 0.5
		, const int max_endurance = 25): Character(health), 
		m_adrenaline(adrenaline), m_endurance(endurance), MAX_ADRENALINE(max_adren), MAX_ENDURANCE(max_endurance)
	{
		// well the player cannot start off dead, now can he?
		m_isAlive = true;
		InitAbilities();
	}
	~Player()
	{
		std::vector<Ability*>::iterator i;
		for(i = m_abilities.begin(); i != m_abilities.end(); i++)
		{
			delete *i;
		}
		m_abilities.clear();
	}

	double GetCurrentAdrenaline();
	int GetEndurance();
	void IncreaseEndurance(int amount);
	void DecreaseEndurance(int amount);
	void IncreaseAdrenalineLevel(double amount);
	void DecreaseAdrenalineLevel(double amount);
	void SetAdrenaline(double amount);
	int GetDamage();
	double Attack();
	void DisplayAbilities();
	void InitAbilities();
	int ChooseAnAttack();
	Ability* ValidateEnduranceLevel();
private:
	double m_adrenaline;
	int m_endurance;
	const int MAX_ENDURANCE;
	const double MAX_ADRENALINE;
	std::vector<Ability*> m_abilities;
};

#endif