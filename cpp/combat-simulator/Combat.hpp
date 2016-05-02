/*********************************************************************
** Program Filename: Combat.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Handles combat between any two Creature subclasses
** Input:            Needs two points to creatures to engage in combat
** Output:           Prints dice rolls and other combat information
**                   and updates creatures status as appropriate
********************************************************************/

#ifndef SSHILLYER_COMBAT_HPP
#define SSHILLYER_COMBAT_HPP

#include "Creature.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

class Combat
{
private:
  Creature* creatures[2];
  int current_round;
  bool combatant_dead;
  Combat(); // Non public
  void resolve_round();
  void resolve_attack(int);
public:
  Combat(Creature*, Creature*);
  ~Combat();
  int resolve_combat();
  void print_summary(int);
};

#endif
