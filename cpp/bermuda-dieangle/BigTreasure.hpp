/*********************************************************************
** Program Filename: BigTreasure.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can use while in the Trench
**                   to escape to surface.
** Input:            None.
** Output:           Using in correct zone can update player status
**                   to win the game.
********************************************************************/
#ifndef SSHILLYER_BIGTREASURE_HPP
#define SSHILLYER_BIGTREASURE_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Space.hpp"
#include "UserInterface.hpp"

class Player; // forward declaration

class BigTreasure : public Item
{
private:
public:
  BigTreasure();
  void use(Player* player);
};

#endif
