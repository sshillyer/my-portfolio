/*********************************************************************
** Program Filename: Creature.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      A Creature class. Has attack dice, defense dice,
**                   strength (health), and armor values. Can have
**                   a special active and a torn tendon
** Input:            None
** Output:           Base class for concrete subclasses
********************************************************************/

#include "Creature.hpp"


/*********************************************************************
** Function:         Creature()
** Description:      Constructor
** Parameters:       NA
** Pre-Conditions:   None
** Post-Conditions:  Creature created
********************************************************************/
Creature::Creature()
{
	this->special_active = false;
	this->torn_tendon = false;
	this->name = "Nameless";
}


/*********************************************************************
** Function:         Creature()
** Description:      Constructor
** Parameters:       string for name
** Pre-Conditions:   None
** Post-Conditions:  Creature created with a name
********************************************************************/
Creature::Creature(std::string name)
{
	this->special_active = false;
	this->torn_tendon = false;
	this->name = name;
}


/*********************************************************************
** Function:         ~Creature()
** Description:      Destructor
** Parameters:       NA
** Pre-Conditions:   None
** Post-Conditions:  Creature destroyed
********************************************************************/
Creature::~Creature()
{
}


/*********************************************************************
** Function:         attack_roll()
** Description:      Makes the appropriate type of die and rolls it
**                   the appropriate number of times
** Parameters:       None
** Pre-Conditions:   Creature must have data members set
** Post-Conditions:  Prints result of each roll and returns the total
**                   of all rolls (if multiple)
********************************************************************/
int Creature::attack_roll()
{
	int total_roll = 0, roll = 0;
	Die* die = new Die(this->attack_dice_sides);

	for (int i = 0; i < this->attack_dice_count; i++)
	{
		roll = die->roll();
		total_roll += roll;
		// std::cout << this->type_name << " rolls attack die: d" << attack_dice_sides << " for " << roll << "\n";
	}
	std::cout << "Total attack roll: " << total_roll << "\n";

	delete die;
	return total_roll;
}


/*********************************************************************
** Function:         defense_roll()
** Description:      Makes the appropriate type of die and rolls it
**                   the appropriate number of times
** Parameters:       None
** Pre-Conditions:   Creature must have data members set
** Post-Conditions:  Prints result of each roll and returns the total
**                   of all rolls (if multiple)
********************************************************************/
int Creature::defense_roll()
{
	int total_roll = 0, roll = 0;
	Die* die = new Die(this->defense_dice_sides);

	for (int i = 0; i < this->defense_dice_count; i++)
	{
		roll = die->roll();
		total_roll += roll;
		// std::cout << this->type_name << " rolls defense die: d" << defense_dice_sides << " for " << roll << "\n";
	}
	std::cout << "Total defense roll: " << total_roll << "\n";

	delete die;
	return total_roll;
}


/*********************************************************************
** Function:         update_strength()
** Description:      Decrements a Creature's strenght by argument value
** Parameters:       an integer representing dmage done
** Pre-Conditions:   Damage must be passed in as arg
** Post-Conditions:  Strength is reduced based on damage and message
**                   printed to screen.
********************************************************************/
void Creature::update_strength(int damage)
{
	this->strength -= damage;
}


/*********************************************************************
** Function:         check_armor()
** Description:      Returns value of Creature's armor
** Parameters:       None
** Pre-Conditions:   Creature must be Instantiated
** Post-Conditions:  Prints armor value and returns to caller
********************************************************************/
int Creature::check_armor()
{
	return this->armor;
}

/*********************************************************************
** Function:         check_strength()
** Description:      Return strength
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns strength value to caller
********************************************************************/
int Creature::check_strength()
{
	return this->strength;
}


/*********************************************************************
** Function:         print_stats()
** Description:      Prints current status of Creature
** Parameters:       None
** Pre-Conditions:   Creature must exist
** Post-Conditions:  Prints current status of Creature
********************************************************************/
void Creature::print_stats()
{
	std::string bar(25, '~');
	std::cout << bar << '\n';
	std::cout << "Name: " << this->name << "\n";
	std::cout << "Type: \t" << this->type_name << "\n";
	std::cout << "Strength: \t" << this->strength << "\n";
	std::cout << "Tendon Torn: \t" << ((this->torn_tendon) ? "Yes" : "No") << "\n";
	std::cout << bar << '\n';
}


/*********************************************************************
** Function:         get_name()
** Description:      Returns name
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns name
********************************************************************/
std::string Creature::get_name()
{
	return this->name;
}


/*********************************************************************
** Function:         get_type_name()
** Description:      Returns name
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns type name
********************************************************************/
std::string Creature::get_type_name()
{
	return this->type_name;
}


/*********************************************************************
** Function:         tear_tendon()
** Description:      sets torn_tendon to true
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  torn_tendon = true
********************************************************************/
void Creature::tear_tendon()
{
	this->torn_tendon = true;
}


/*********************************************************************
** Function:         toggle_special_off()
** Description:      sets special_active to false
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  special_active = false
********************************************************************/
void Creature::toggle_special_off()
{
	this->special_active = false;
}


/*********************************************************************
** Function:         toggle_special_off()
** Description:      sets special_active to false
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  special_active = false
********************************************************************/
bool Creature::has_special_active()
{
	return this->special_active;
}


/*********************************************************************
** Function:         has_torn_tendon()
** Description:      returns torn_tendon value
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  returns torn_tendon value
********************************************************************/
bool Creature::has_torn_tendon()
{
	return this->torn_tendon;
}


/*********************************************************************
** Function:         reset()
** Description:      Resets the status effects and strength of creature
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Resets the status effects and strength of creature
********************************************************************/
void Creature::reset()
{
	this->special_active = false;
	this->torn_tendon = false;
	this->strength = this->default_strength;
}


/*********************************************************************
** Function:         revive()
** Description:      Heals some of creatures health and removes status
**                   effects
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Resets the status effects and strength of creature
********************************************************************/
void Creature::revive()
{
	this->special_active = false;
	this->torn_tendon = false;
	update_strength(-((this->default_strength - this->strength) / 2));
}
