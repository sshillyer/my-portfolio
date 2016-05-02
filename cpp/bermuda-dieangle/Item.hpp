/*********************************************************************
** Program Filename: Item.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Abstract Item class. Remembers label, hint, and
**                   number of uses for items.
** Input:            None direct (abstract)
** Output:           None direct (abstract)
********************************************************************/
#ifndef SSHILLYER_ITEM_HPP
#define SSHILLYER_ITEM_HPP

#include <iostream>
#include <string>

class Player; // forward declaration

class Item {
protected:
  std::string label;
  std::string hint;
  int num_uses;

public:
  Item();
  virtual void use(Player* player) =0;
  bool is_depleted();
  std::string get_label();
  void inspect();
};

#endif
