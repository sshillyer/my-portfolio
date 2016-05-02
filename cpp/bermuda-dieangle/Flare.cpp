/*********************************************************************
** Program Filename: Flare.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can use to reveal all exits
** Input:            None.
** Output:           Using updates all current location's exits
********************************************************************/
#include "Flare.hpp"


/*********************************************************************
** Function:         Flare()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Sets the label and hint for the item.
********************************************************************/
Flare::Flare() : Item() {
  this->label = "Underwater Flare";
  this->hint = "Illuminates an area, revealing all exits.";
  this->num_uses = 3;
}


/*********************************************************************
** Function:         use()
** Description:      Defines pure virtual function use().
** Parameters:       Pointer to Player
** Pre-Conditions:   Player must exist; item should be in DivingBelt
** Post-Conditions:  Using updates all current location's exits
********************************************************************/
void Flare::use(Player* player) {
  Space* location = player->current_location();
  for (int i = 0; i < 4; i++) {
    location->reveal(i);
  }
  std::cout << "You've revealed all of the exits!\n";
  num_uses--;
}
