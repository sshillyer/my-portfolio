/*********************************************************************
** Program Filename: BlueMen.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Subclass of Creature class
** Input:            None
** Output:           See Creature class
********************************************************************/

#include "BlueMen.hpp"


/*********************************************************************
** Function:         BlueMen()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  BlueMen fully initialized
********************************************************************/

BlueMen::BlueMen(std::string name)
{
	this->name = name;
	this->type_name = "Blue Men";

	// 2d10 attack
	this->attack_dice_sides = 10;
	this->attack_dice_count = 2;

	// 3d6 defense
	this->defense_dice_sides = 6;
	this->defense_dice_count = 3;

	this->armor = 3;
	this->strength = 12;
	this->default_strength = 12;
}

/*********************************************************************
** Function:         revive()
** Description:      Heals some of creatures health and removes status
**                   effects
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Resets the status effects and strength of creature
********************************************************************/
void BlueMen::revive()
{
	this->special_active = false;
	this->torn_tendon = false;
	std::cout << "The blue men tend to each other's wounds as best they can!\n";
	update_strength(-((this->default_strength - this->strength) / 4));
}
