/*********************************************************************
** Program Filename: TheShadow.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Subclass of Creature class
** Input:            None
** Output:           See Creature class
********************************************************************/

#include "TheShadow.hpp"


/*********************************************************************
** Function:         TheShadow()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  TheShadow fully initialized
********************************************************************/
TheShadow::TheShadow(std::string name)
{
	this->name = name;
	this->type_name = "The Shadow";

	// 2d10 attack
	this->attack_dice_sides = 10;
	this->attack_dice_count = 2;

	// 1d6 defense
	this->defense_dice_sides = 6;
	this->defense_dice_count = 1;

	this->armor = 0;
	this->strength = 12;
	this->default_strength = 12;
}


/*********************************************************************
** Function:         check_armor()
** Description:      Overrides base class method. 50% chance to turn
**                   on TheShadow's special ability
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns the armor value and toggles the special
**                   on ~50% of the time
********************************************************************/
int TheShadow::check_armor()
{
  this->special_active = false;
  if (rand() % 2 == 1)
  {
    special_active = true;
  }
  return this->armor;
}
