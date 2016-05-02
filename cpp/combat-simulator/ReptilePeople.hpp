/*********************************************************************
** Program Filename: ReptilePeople.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Subclass of Creature class
** Input:            None
** Output:           See Creature class
********************************************************************/

#ifndef SSHILLYER_REPTILEPEOPLE_HPP
#define SSHILLYER_REPTILEPEOPLE_HPP

#include "Creature.hpp"

class ReptilePeople : public Creature
{
private:
public:
  ReptilePeople(std::string);
  virtual void revive();
};

#endif
