/*********************************************************************
** Program Filename: Combat.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Handles combat between any two Creature subclasses
** Input:            Needs two points to creatures to engage in combat
** Output:           Prints dice rolls and other combat information
**                   and updates creatures status as appropriate
********************************************************************/

#include "Combat.hpp"

/*********************************************************************
** Function:         Combat()
** Description:      Default Constructor. Here for extensibility purposes
** Parameters:       None
** Pre-Conditions:   Seed must be seeded outside class in main program
** Post-Conditions:
********************************************************************/
Combat::Combat()
{
	this->current_round = 0;
	this->combatant_dead = false;
}


/*********************************************************************
** Function:         Combat(Creature*, Creature*)
** Description:      Instantiates the class and seeds the random numbs
** Parameters:       Two pointers to Creature
** Pre-Conditions:   Seed must be seeded outside class in main program
**                   Creatures must exist
** Post-Conditions:  Combat class exists
********************************************************************/

Combat::Combat(Creature* creature_a, Creature* creature_b)
{
	this->current_round = 0;
	this->combatant_dead = false;
	this->creatures[0] = creature_a;
	this->creatures[1] = creature_b;
}


/*********************************************************************
** Function:         ~Combat()
** Description:      Destructor. Performs nothing currently.
** Parameters:       .
** Pre-Conditions:   .
** Post-Conditions:  .
********************************************************************/
Combat::~Combat()
{
}


/*********************************************************************
** Function:         resolve_combat()
** Description:      Logic flow to ensure combat continues until a
**                   creature is dead, per combatant_dead data member
** Parameters:       None
** Pre-Conditions:   Combat class must be instantiated to call
** Post-Conditions:  Returns an int indicated which creature index
**                   was victorious
********************************************************************/
int Combat::resolve_combat()
{
	// Print Header
	std::string bar(creatures[0]->get_name().length() + creatures[1]->get_name().length() + 5, '=');
	std::cout << bar << "\n";
	std::cout << creatures[0]->get_name() << " vs. " << creatures[1]->get_name() << "\n";
	std::cout << bar << "\n";

	// Execute resolve_round until a creature is dead
	while (!combatant_dead)
	{
		current_round++;
		resolve_round();
	}
	// Determine winner by checking which one still has health
	int winner_index = (creatures[0]->check_strength() > 0) ? 0 : 1;

	print_summary(winner_index);
	return winner_index; // used to track who won for statistics
}

/*********************************************************************
** Function:         resolve_round()
** Description:      Handles sub-logic of a single round of combat
**                   where each creature attacks once unless one dies
** Parameters:       None
** Pre-Conditions:   Called by resolve_combat()
** Post-Conditions:  One or both creatures will have made their attack
********************************************************************/
void Combat::resolve_round()
{
	// Print header
	std::string bar(20, '*');
	std::cout << bar << "\n";
	std::cout << "   Attack round " << current_round << "!\n" << bar << "\n";

	int atk_i = rand() % 2;  // randomly pick a creature to attack first
	int turn = 0;           // Make sure we only do two attacks
	while (turn < 2 && !combatant_dead)
	{
		resolve_attack(atk_i);
		atk_i = (atk_i == 0) ? 1 : 0;
		turn++;
	}
}


/*********************************************************************
** Function:         ()
** Description:      .
** Parameters:       .
** Pre-Conditions:   .
** Post-Conditions:  .
**                   .
********************************************************************/
void Combat::resolve_attack(int atk_i)
{
	int def_i = (atk_i == 0) ? 1 : 0; // defender index
	int attack_roll = creatures[atk_i]->attack_roll();
		std::cout << creatures[atk_i]->get_name() << atk_i+1 << " attacks!\n";

	// Handle goblin cut tendons debuff
	if (creatures[atk_i]->has_torn_tendon())
	{
		attack_roll /= 2;
		std::cout << "!!! " << creatures[atk_i]->get_name() << " has a torn tendon. Attack halved to " << attack_roll << "!\n";
	}

	if (creatures[atk_i]->has_special_active())
	{
		// tear defenders tendon and print message only the first time it happens
		if(!creatures[def_i]->has_torn_tendon() && creatures[def_i]->get_type_name() != "Goblin")
		{
				creatures[def_i]->tear_tendon();
				std::cout << "!!! Goblin has torn " << creatures[def_i]->get_name() << "'s tendon!\n";
		}
		creatures[atk_i]->toggle_special_off();
	}

	// Process defense roll
	int defense_roll = creatures[def_i]->defense_roll();
	int defender_armor = creatures[def_i]->check_armor();
	int damage_done = 0;

	// Handle TheShadow's special armor case
	if (creatures[def_i]->has_special_active())
	{
		std::cout << "!!! The Shadow has tricked its opponent! The attack misses!\n";
		creatures[def_i]->toggle_special_off();
	}
	else // Every other defense is handled here
	{
		damage_done = attack_roll - defense_roll - defender_armor;
		if (damage_done > 0)
		{
			creatures[def_i]->update_strength(damage_done);
			std::cout << creatures[atk_i]->get_name() << "'s attack does " << damage_done << " damage!\n";
		}
	}

	if (creatures[def_i]->check_strength() <= 0)
	{
		this->combatant_dead = true;
		std::cout << creatures[def_i]->get_name() << " has fallen in battle!\n";
	}
	for (int i = 0; i < 2; i++)
	{
		creatures[i]->print_stats();
	}
}


/*********************************************************************
** Function:         print_summary()
** Description:      Prints class name of winner
** Parameters:       index of the winner
** Pre-Conditions:   A winner must be determined and passed as arg
** Post-Conditions:  Prints info to screen
********************************************************************/
void Combat::print_summary(int winner)
{
	std::string bar(30, '=');
	std::cout << bar << "\n";
	std::cout << "The Winner is " << creatures[winner]->get_name() << " (" << winner+1 << ")!!!\n";
	std::cout << bar << "\n\n";
}
