/*********************************************************************
** Program Filename: Ship.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#ifndef SSHILLYER_SHIP_HPP
#define SSHILLYER_SHIP_HPP

#include "BigTreasure.hpp"
#include "OxygenTank.hpp"
#include "Space.hpp"
#include "Player.hpp"
#include "UserInterface.hpp"

class Ship : public Space {
public:
  Ship(std::string label);
  void special(Player* player);
  std::string get_menu_option();
  void print_description();
  std::string get_type();
};

#endif
