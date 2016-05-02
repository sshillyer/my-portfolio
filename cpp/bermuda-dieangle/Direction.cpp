/*********************************************************************
** Program Filename: Direction.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Simple class that returns a direction and string
**                   depending on which integer is passed in
** Input:            An integer
** Output:           The string representing that direction.
********************************************************************/
#include "Direction.hpp"

std::string Direction::labels[4] = {"North", "East", "South", "West" };

/*********************************************************************
** Function:         get_direction()
** Description:      Static member to return a direction as as tring
** Parameters:       integer representing a direction
** Pre-Conditions:   None
** Post-Conditions:  Returns a string
********************************************************************/
std::string Direction::get_direction(int i)  {
  if (0 <= i && i <= 3)
    return labels[i];
  else
    throw std::string("Direction::get_direction() passed invalid value\n");
}
