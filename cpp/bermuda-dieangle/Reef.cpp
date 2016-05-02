/*********************************************************************
** Program Filename: Reef.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#include "Reef.hpp"


/*********************************************************************
** Function:         Reef()
** Description:      Constructor. Sets the label for the area.
** Parameters:       String for the label.
** Pre-Conditions:   None
** Post-Conditions:  Label is initialized
********************************************************************/
Reef::Reef(std::string label) : Space(label) {
  OxygenTank* oxygen = new OxygenTank;
  RescueBeacon* beacon = new RescueBeacon;

  this->loot_table.push_back(oxygen);
  this->loot_table.push_back(beacon);
}


/*********************************************************************
** Function:         special()
** Description:      Player can try to find gear on the bodies
** Parameters:       Player* player
** Pre-Conditions:   None
** Post-Conditions:  Player searches through the bodies and gets loot
********************************************************************/
void Reef::special(Player* player) {
  if (!special_used) {
    std::cout << "You explore the reef.\n";
    std::cout << "Amidst the coral, you find a body impaled on the coral. You search the body...\n";
    Item* loot = get_loot();
    player->pickup_item(loot);

    player->update_oxygen(-15);
    this->special_used = true;
  }
  else {
    std::cout << "You've already explored this reef.\n";
  }
}


/*********************************************************************
** Function:         get_menu_option()
** Description:      return the option to display for this menu
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  returns a string
********************************************************************/
std::string Reef::get_menu_option() {
  if (!special_used) {
    return "Explore the coral reef and search for gear in the wreckage\n";
  }
  else {
    return "[You've already explored this reef.]\n";
  }
}


/*********************************************************************
** Function:         print_description()
** Description:      Handles printing the description of the area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Will print the description to user interface
********************************************************************/
void Reef::print_description() {
  UserInterface::print_file("text/reef.txt");
  Space::print_description();
}


/*********************************************************************
** Function:         get_type()
** Description:      Returns a string representing the type of area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  None
********************************************************************/
std::string Reef::get_type() {
  return "Reef";
}
