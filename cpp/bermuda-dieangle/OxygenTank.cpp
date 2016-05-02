/*********************************************************************
** Program Filename: OxygenTank.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can replenish oxygen
** Output:           Using increases player's oxygen levels
********************************************************************/
#include "OxygenTank.hpp"


/*********************************************************************
** Function:         OxygenTank()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Sets the label and hint for the item.
********************************************************************/
OxygenTank::OxygenTank() : Item() {
  this->label = "Spare Oxygen Tank";
  this->hint = "You can use this when your oxygen gets low.";
  this->num_uses = 1;
}


/*********************************************************************
** Function:         use()
** Description:      Defines pure virtual function use().
** Parameters:       Pointer to Player
** Pre-Conditions:   Player must exist; item should be in DivingBelt
** Post-Conditions:  Increases player's oxygen levels.
********************************************************************/
void OxygenTank::use(Player* player) {
  std::cout << "You swap out the oxygen tank.\n";
  player->update_oxygen(100);
  --num_uses;
}
