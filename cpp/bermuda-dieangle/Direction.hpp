/*********************************************************************
** Program Filename: Direction.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Simple class that returns a direction and string
**                   depending on which integer is passed in
** Input:            An integer
** Output:           The string representing that direction.
********************************************************************/
#ifndef SSHILLYER_DIRECTION_HPP
#define SSHILLYER_DIRECTION_HPP

#include <string>

class Direction
{
private:
  static std::string labels[4];
  Direction(); // Not meant to be instantiated, static method only
public:
  static std::string get_direction(int i);
};

#endif
