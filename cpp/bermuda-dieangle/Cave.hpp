/*********************************************************************
** Program Filename: Cave.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#ifndef SSHILLYER_CAVE_HPP
#define SSHILLYER_CAVE_HPP

#include "Flare.hpp"
#include "Flippers.hpp"
#include "Space.hpp"
#include "Player.hpp"
#include "UserInterface.hpp"

class Cave : public Space {
public:
  Cave(std::string label);
  void special(Player* player);
  std::string get_menu_option();
  void print_description();
  std::string get_type();
};

#endif
