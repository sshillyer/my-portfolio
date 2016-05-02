/*********************************************************************
** Program Filename: Cave.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#include "Cave.hpp"

/*********************************************************************
** Function:         Cave()
** Description:      Constructor. Sets the loot for the area.
** Parameters:       A label for this particular space.
** Pre-Conditions:   None
** Post-Conditions:  loot_table will be populated with the items.
********************************************************************/
Cave::Cave(std::string label) : Space(label) {
  Flare* flare = new Flare; // NOTE I changed this from Item* to Flare* and same with next line
  Flippers* flippers = new Flippers;

  this->loot_table.push_back(flare);
  this->loot_table.push_back(flippers);
}


/*********************************************************************
** Function:         special()
** Description:      Allows the player to search the cave for treasure
** Parameters:       Player* player
** Pre-Conditions:   None
** Post-Conditions:  Player gets loot or is told they already searched
********************************************************************/
void Cave::special(Player* player) {
  if (!special_used) {
    this->special_used = true;
    std::cout << "You search the cave for treasure.\n";
    Item* loot = get_loot();
    player->pickup_item(loot);
    player->update_oxygen(-8);
  }

  else {
    std::cout << "You've already searched this location.\n";
  }
}


/*********************************************************************
** Function:         get_menu_option()
** Description:      return the option to display for this menu
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  returns a string
********************************************************************/
std::string Cave::get_menu_option() {
  if (!special_used) {
    return "Search for Treasure\n";
  }
  else {
    return "[You've already searched here.]\n";
  }
}


/*********************************************************************
** Function:         print_description()
** Description:      Handles printing the description of the area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Will print the description to user interface
********************************************************************/
void Cave::print_description() {
  UserInterface::print_file("text/cave.txt");
  Space::print_description();
}


/*********************************************************************
** Function:         get_type()
** Description:      Returns a string representing the type of area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  None
********************************************************************/
std::string Cave::get_type(){
  return "Cave";
}
