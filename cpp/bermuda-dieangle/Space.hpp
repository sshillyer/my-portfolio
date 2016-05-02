/*********************************************************************
** Program Filename: Space.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      A Space abstract class that works as a data
**                   structure. A Map can hold Space nodes s othat a
**                   player can move around. Nodes can be linked.
** Input:            Label for each Space node.
** Output:           None directly (Abstract class)
********************************************************************/
#ifndef SSHILLYER_SPACE_HPP
#define SSHILLYER_SPACE_HPP

#include "Direction.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "UserInterface.hpp"

#include <cstddef>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

class Player; // forward declaration

class Space {
protected:
  std::string label;
  Space* north;
  Space* east;
  Space* south;
  Space* west;
  bool revealed[4];
  bool special_used;
  std::vector<Item*> loot_table;

public:
  Space(std::string label = "Default");
  ~Space();
  std::string get_label();
  virtual std::string get_menu_option() =0;
  virtual void print_description();
  virtual void special(Player* player) =0; // pure virtual
  void link(int direction, Space* location);
  Space* location_at(int direction);
  void reveal(int direction);
  bool is_revealed(int direction);
  Item* get_loot();
  virtual std::string get_type() =0;
  bool is_special_used() {
    return special_used;
  }
};

#endif
