/*********************************************************************
** Program Filename: RescueBeacon.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can use to win game
** Input:            None.
** Output:           If in Ocean space then can win game if they wait
**                   and have enough oxygen to survive.
********************************************************************/
#ifndef SSHILLYER_RESCUEBEACON_HPP
#define SSHILLYER_RESCUEBEACON_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Space.hpp"
#include "UserInterface.hpp"

class Player;

class RescueBeacon : public Item {
private:
public:
  RescueBeacon();
  void use(Player* player);
};

#endif
