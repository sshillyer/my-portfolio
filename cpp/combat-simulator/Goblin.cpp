/*********************************************************************
** Program Filename: Goblin.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Subclass of Creature class
** Input:            None
** Output:           See Creature class
********************************************************************/

#include "Goblin.hpp"


/*********************************************************************
** Function:         Goblin()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Goblin fully initialized
********************************************************************/

Goblin::Goblin(std::string name = "Unnamed")
{
	this->name = name;
	this->type_name = "Goblin";

	// 2d6 attack
	this->attack_dice_sides = 6;
	this->attack_dice_count = 2;

	// 1d6 defense
	this->defense_dice_sides = 6;
	this->defense_dice_count = 1;

	this->armor = 3;
	this->strength = 8;
	this->default_strength = 8;

}


/*********************************************************************
** Function:         attack_roll()
** Description:      Overrides base class attack roll
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  IF goblin rolls a 12, then turns on special_active
**                   (Turned off by combat class)
********************************************************************/
int Goblin::attack_roll()
{
  this->special_active = false;
  int roll = Creature::attack_roll();
  if (roll == 12)
  {
    special_active = true;
  }
  return roll;
}

/*********************************************************************
** Function:         revive()
** Description:      Heals some of creatures health and removes status
**                   effects
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Resets the status effects and strength of creature
********************************************************************/
void Goblin::revive()
{
	this->special_active = false;
	this->torn_tendon = false;
	std::cout << name << " eats the heart of his enemy and doubles in size!\n";
	update_strength(-(this->default_strength));
}
