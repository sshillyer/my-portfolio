/*********************************************************************
** Program Filename: OxygenTank.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can replenish oxygen
** Output:           Using increases player's oxygen levels
********************************************************************/
#ifndef SSHILLYER_OXYGENTANK_HPP
#define SSHILLYER_OXYGENTANK_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Space.hpp"

class Player; // Forward declaration

class OxygenTank : public Item {
public:
  OxygenTank();
  void use(Player* player);
};

#endif
