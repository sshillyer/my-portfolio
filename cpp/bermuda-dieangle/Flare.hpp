/*********************************************************************
** Program Filename: Flare.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can use to reveal all exits
** Input:            None.
** Output:           Using updates all current location's exits
********************************************************************/
#ifndef SSHILLYER_FLARE_HPP
#define SSHILLYER_FLARE_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Space.hpp"

class Player;

class Flare : public Item {
public:
  Flare();
  void use(Player* player);
};

#endif
