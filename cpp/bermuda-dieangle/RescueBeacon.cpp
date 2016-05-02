/*********************************************************************
** Program Filename: RescueBeacon.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can use to win game
** Input:            None.
** Output:           If in Ocean space then can win game if they wait
**                   and have enough oxygen to survive.
********************************************************************/
#include "RescueBeacon.hpp"


/*********************************************************************
** Function:         RescueBeacon()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Sets the label and hint for the item.
********************************************************************/
RescueBeacon::RescueBeacon() : Item() {
  this->label = "Advanced Rescue Beacon";
  this->hint = "If you activate and tread water in the open sea you might get rescued.";
  this->num_uses = 1;
}


/*********************************************************************
** Function:         use()
** Description:      Defines pure virtual function use().
** Parameters:       Pointer to Player
** Pre-Conditions:   Player must exist; item should be in DivingBelt
** Post-Conditions:  If player is in Ocean, can wait and win game
********************************************************************/
void RescueBeacon::use(Player* player) {
  Space* location = player->current_location();
  if (location->get_type() == "Ocean") {
    std::cout << "The beacon's indicator flashes green. Do you wait?\n";
    char input = UserInterface::yes_or_no();

    if (input == 'Y') {
      std::cout << "You tread water and wait for rescue...\n";
      player->update_oxygen(-10);
      if (player->get_oxygen() > 0) {
        player->set_win();
      }
    }

    else {
      std::cout << "You decide not to wait.\n";
    }
  }

  else {
    std::cout << "The beacon blinks red... you apparently need to be in open water.\n";
  }

  player->update_oxygen(-1);
}
