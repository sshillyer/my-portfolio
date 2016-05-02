/*********************************************************************
** Program Filename: Die.cpp
** Author:           Shawn Hillyer
** Date:             10/27/2015
** Description:      Simple class to roll dice
** Input:            int to set num_sides
** Output:           Returns an int from 1 to num_sides
********************************************************************/
#include <cstdlib>
#include "Die.hpp"


/*********************************************************************
** Function:         Die()
** Description:      Default constructor
** Parameters:       int sides; defaults to 6
** Pre-Conditions:   Called during instantiation
** Post-Conditions:  New Die object created fully initialized
********************************************************************/
Die::Die(int sides)
{
	set_num_sides(sides);
}


/*********************************************************************
** Function:         set_num_sides()
** Description:      Validates and sets num_sides member variable
** Parameters:       int sides is validated and assigned to num_sides
** Pre-Conditions:   object must be instantiated to call; private func.
** Post-Conditions:  num_sides will be initialized
********************************************************************/
void Die::set_num_sides(int sides)
{
	if (sides < 4) // smallest number of sides on a die is 4
	{
		num_sides = 4;
	}
	else
	{
		num_sides = sides;
	}
}


/*********************************************************************
** Function:        roll()
** Description:     Simulates a roll of a fair die
** Parameters:      None
** Pre-Conditions:  Object must be instantiated
** Post-Conditions: Returns an int from range [1, num_sides] inclusive
********************************************************************/
int Die::roll()
{
	int roll = rand() % num_sides + 1; //
	return roll;
}
