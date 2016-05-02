/*********************************************************************
** Program Filename: TheShadow.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Subclass of Creature class
** Input:            None
** Output:           See Creature class
********************************************************************/

#ifndef SSHILLYER_THESHADOW_HPP
#define SSHILLYER_THESHADOW_HPP

#include "Creature.hpp"
#include <cstdlib>

class TheShadow : public Creature
{
private:
public:
  TheShadow(std::string);
  int check_armor(); // override virtal function
};

#endif
