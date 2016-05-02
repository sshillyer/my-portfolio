/*********************************************************************
** Program Filename: Flippers.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Halves move/search costs.
** Input:            None.
** Output:           Notifies player wearing, havles movement/search cost
********************************************************************/
#ifndef SSHILLYER_FLIPPERS_HPP
#define SSHILLYER_FLIPPERS_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Space.hpp"

class Player;

class Flippers : public Item {
public:
  Flippers();
  void use(Player* player);
};

#endif
