#include "Player.h"

double Player::Attack()
{
	double damage = 0;
	
	Ability* ability = ValidateEnduranceLevel();

	bool abilityChosen = false;
	damage = ability->GetDamage();
	DecreaseEndurance(ability->GetCost());
	if(ability->GetEnduranceReturn() > 0)
	{
		IncreaseEndurance(ability->GetEnduranceReturn());
	}
	std::cout << ability->GetDescription() << "\n";
	// if the playe's adrenaline is higher than 0, multiply the damage by it.
	if(m_adrenaline > 0)
	{
		damage *= m_adrenaline;
	}
	return damage;
}

// This loops through the attack, finds the chosen one, and makes sure the 
// player has enough endurance. If they do not, theyre asked to choose again
Ability* Player::ValidateEnduranceLevel()
{
	int counter = 1;
	bool hasEnoughEndurance = false;
	int choice = 0;
	Ability* ability;
	do
	{
		choice = ChooseAnAttack();
		std::vector<Ability*>::iterator itr;
		for(itr = m_abilities.begin(); itr != m_abilities.end(); itr++)
		{
			if(counter == choice)
			{
				int end = (*itr)->GetCost();
				if(end <= GetEndurance())
				{
					hasEnoughEndurance = true;
					ability = *itr;
					break;
				}
				else
				{
					std::cout << "Not enough adrenaline, please choose another ability\n";
				}
			}
			counter++;
		}
	}while(!hasEnoughEndurance);
	return ability;
}

double Player::GetCurrentAdrenaline()
{
	return m_adrenaline;
}
int Player::GetEndurance()
{
	return m_endurance;
}
void Player::IncreaseEndurance(int amount)
{
	m_endurance += amount;
	if(m_endurance > MAX_ENDURANCE)
	{
		m_endurance = MAX_ENDURANCE;
	}
}
void Player::DecreaseEndurance(int amount)
{
	m_endurance -= amount;
	if(m_endurance < 0)
	{
		m_endurance = 0;
	}
}
void Player::IncreaseAdrenalineLevel(double amount)
{
	m_adrenaline += amount;
	if(m_adrenaline > MAX_ADRENALINE)
	{
		m_adrenaline = MAX_ADRENALINE;
	}
}
void Player::DecreaseAdrenalineLevel(double amount)
{
	m_adrenaline -= amount;
	if(m_adrenaline < 0)
	{
		m_adrenaline = 0;
	}
}

void Player::SetAdrenaline(double amount)
{
	m_adrenaline = amount;
}
void Player::DisplayAbilities()
{
	std::vector<Ability*>::iterator itr;
	int counter = 1;	
	for(itr = m_abilities.begin(); itr != m_abilities.end(); itr++)
	{
		Ability* ability = *itr;
		std::cout << counter << ": " << ability->GetName() << " cost: " << 
			ability->GetCost() << " damage: " << ability->GetDamage() <<"\n";
		counter++;
	}
}
void Player::InitAbilities()
{
	m_abilities.push_back(new Ability("Punch", "You punch the enemy in the stomach", 5, 6));
	m_abilities.push_back(new Ability("Kick", "You kick the enemy in the chest", 8, 9));
	m_abilities.push_back(new Ability("Knife Stab", "You draw your knife and stab the enemy in the left kidney", 14, 12));
	m_abilities.push_back(new Ability("Hand Gun", "You draw your P14 and shoot the enemy in the head.", 100, 25));
	m_abilities.push_back(new Ability("pass", "You pass on your attack.", 0, 0, 10));
}

int Player::ChooseAnAttack()
{
	std::string input;
	std::cout << "You have " << GetEndurance() << 
		" endurance and " << GetCurrentAdrenaline() << " adrenaline.\nType in the number for the ability you wish to use\n";
	DisplayAbilities();
	std::getline(std::cin, input);
	return atoi(input.c_str());	
}