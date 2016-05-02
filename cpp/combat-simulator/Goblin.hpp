/*********************************************************************
** Program Filename: Goblin.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Subclass of Creature class
** Input:            None
** Output:           See Creature class
********************************************************************/

#ifndef SSHILLYER_GOBLIN_HPP
#define SSHILLYER_GOBLIN_HPP

#include "Creature.hpp"
#include <cstdlib>

class Goblin : public Creature
{
private:
public:
  Goblin(std::string);
  int attack_roll(); // override virtual function
  virtual void revive();
};

#endif
