/*********************************************************************
** Program Filename: Reef.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#ifndef SSHILLYER_REEF_HPP
#define SSHILLYER_REEF_HPP

#include "Space.hpp"
#include "RescueBeacon.hpp"
#include "OxygenTank.hpp"

class Reef : public Space {
public:
  Reef(std::string label);
  void special(Player* player);
  std::string get_menu_option();
  void print_description();
  std::string get_type();
};

#endif
