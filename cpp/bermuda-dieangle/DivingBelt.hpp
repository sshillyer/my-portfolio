/*********************************************************************
** Program Filename: DivingBelt.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Bag-like structure to hold items; provides an
**                   interface to user.
** Input:            User input and items to add
** Output:           Prints menus and allows client to manipulate
**                   the items in the bag.
********************************************************************/
#ifndef SSHILLYER_DIVINGBELT_HPP
#define SSHILLYER_DIVINGBELT_HPP

#include "Item.hpp"
#include "Menu.hpp"
#include "UserInterface.hpp"
#include <cstddef>
#include <iostream>

class Player; // forward declaration

class DivingBelt {
private:
  int quantity;
  int max_size;
  Item* items[7];
  Menu belt_menu;

public:
  DivingBelt();
  ~DivingBelt();
  bool add_item(Item* new_item);
  void use_item(int item_num, Player* player);
  bool remove_item(int item_num);
  int get_quantity();
  void print_items(Player* player);
};

#endif
