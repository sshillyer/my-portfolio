/*********************************************************************
** Program Filename: Flippers.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Halves move/search costs.
** Input:            None.
** Output:           Notifies player wearing, havles movement/search cost
********************************************************************/
#include "Flippers.hpp"


/*********************************************************************
** Function:         Flippers()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Sets the label and hint for the item.
********************************************************************/
Flippers::Flippers() : Item() {
  this->label = "Speedo Flippers";
  this->hint = "Doubles your swimspeed, halving Oxygen costs for searching and moving.";
  this->num_uses = 1;
}


/*********************************************************************
** Function:         use()
** Description:      Defines pure virtual function use().
** Parameters:       Pointer to Player
** Pre-Conditions:   Player must exist; item should be in DivingBelt
** Post-Conditions:  Notifies player wearing, havles movement/search cost.
********************************************************************/
void Flippers::use(Player* player) {
  player->wear_flippers();
  std::cout << "You wear the upgraded " << label << "!\n";
  num_uses--;
}
