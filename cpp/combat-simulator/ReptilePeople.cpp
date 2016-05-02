/*********************************************************************
** Program Filename: ReptilePeople.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Subclass of Creature class
** Input:            None
** Output:           See Creature class
********************************************************************/

#include "ReptilePeople.hpp"


/*********************************************************************
** Function:         ReptilePeople()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  ReptilePeople fully initialized
********************************************************************/
ReptilePeople::ReptilePeople(std::string name = "Unnamed")
{
	this->name = name;
	this->type_name = "Reptile People";

	// 3d6 attack
	this->attack_dice_sides = 6;
	this->attack_dice_count = 3;

	// 1d6 defense
	this->defense_dice_sides = 6;
	this->defense_dice_count = 1;

	this->armor = 7;
	this->strength = 18;
	this->default_strength = 18;
}


/*********************************************************************
** Function:         revive()
** Description:      Heals some of creatures health and removes status
**                   effects
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Resets the status effects and strength of creature
********************************************************************/
void ReptilePeople::revive()
{
	this->special_active = false;
	this->torn_tendon = false;
	std::cout << name << " regenerates and regrows all missing limbs after battle!\n";
	this->strength = default_strength;
}
