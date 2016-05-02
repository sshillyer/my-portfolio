/*********************************************************************
** Program Filename: BigTreasure.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Item. Can use while in the Trench
**                   to escape to surface.
** Input:            None.
** Output:           Using in correct zone can update player status
**                   to win the game.
********************************************************************/
#include "BigTreasure.hpp"


/*********************************************************************
** Function:         BigTreasure()
** Description:      Constructor
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Sets the label and hint for the item.
********************************************************************/
BigTreasure::BigTreasure() : Item() {
  this->label = "Ancient Artifact";
  this->hint = "You might be able to barter with this, or take it home and sell it!";
  this->num_uses = 1;
}

/*********************************************************************
** Function:         use()
** Description:      Defines pure virtual function use().
** Parameters:       Pointer to Player
** Pre-Conditions:   Player must exist; item should be in DivingBelt
** Post-Conditions:  May cause game to win or player to lose.
********************************************************************/
void BigTreasure::use(Player* player) {
  Space* location = player->current_location();

  // Only lets player win if they went to bottom of trench.
  if (location->get_type() == "Trench" && location->is_special_used()) {
    std::cout << "You examine the Ancient Artifact. You see the image of a Trident on its face.\n";
    std::cout << "Do you give it to the King?\n";

    char input = UserInterface::yes_or_no();
    if (input == 'Y') {
      std::cout << "The MerKing is pleased with your offering. As a thank you, he decides\n";
      std::cout << "to give you safe passage to the closest human-occupied lands.\n";
      player->set_win();
    }

  else // Player is not in trench and the special at that location was used.
    if (input == 'N') {
      std::cout << "The MerKing is angry. He aims his Trident at your chest and sucks all\n";
      std::cout << "of the air from your lungs.\n";
      int oxygen_cost = -1 * player->get_oxygen();
      player->update_oxygen(oxygen_cost);
    }
  }

  // If player is any other zone, do nothing.
  else {
    std::cout << "You admire the Ancient Artifact. It must be priceless!\n";
  }
}
