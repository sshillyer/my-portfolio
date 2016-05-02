/*********************************************************************
** Program Filename: Ship.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#include "Ship.hpp"


/*********************************************************************
** Function:         Ship()
** Description:      Constructor. Sets the label for the area.
** Parameters:       String for the label.
** Pre-Conditions:   None
** Post-Conditions:  Label is initialized
********************************************************************/
Ship::Ship(std::string label) : Space(label) {
  BigTreasure* artifact = new BigTreasure;
  OxygenTank* oxygen = new OxygenTank;

  this->loot_table.push_back(artifact);
  this->loot_table.push_back(oxygen);
}


/*********************************************************************
** Function:         special()
** Description:      Player can try to find treasure on the ship
** Parameters:       Player* player
** Pre-Conditions:   None
** Post-Conditions:  Player searches shipo for loot; might get attacked
**                   by a shark
********************************************************************/
void Ship::special(Player* player) {
  if (!special_used) {
    std::cout << "You explore the ship's wreckage.\n";
    if ((std::rand() % 100) > 70) {
      std::cout << "A nasty shark tries to eat you while you're explorying!\n";
      std::cout << "You expend an extra 10 oxygen, but escape with your life.\n";
      player->update_oxygen(-10);
    }
    Item* loot = get_loot();
    player->pickup_item(loot);

    player->update_oxygen(-15);
    this->special_used = true;
  }
  else {
    std::cout << "You've already explored this ship's wreckage.\n";
  }
}


/*********************************************************************
** Function:         get_menu_option()
** Description:      return the option to display for this menu
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  returns a string
********************************************************************/
std::string Ship::get_menu_option() {
  if (!special_used) {
    return "Explore the ship's wreckage for treasure and gear\n";
  }
  else {
    return "[You've already explored this ship's wreckage]\n";
  }
}


/*********************************************************************
** Function:         print_description()
** Description:      Handles printing the description of the area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Will print the description to user interface
********************************************************************/
void Ship::print_description() {
  UserInterface::print_file("text/ship.txt");
  Space::print_description();
}


/*********************************************************************
** Function:         get_type()
** Description:      Returns a string representing the type of area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  None
********************************************************************/
std::string Ship::get_type() {
  return "Ship";
}
