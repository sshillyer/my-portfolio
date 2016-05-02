/*********************************************************************
** Program Filename: Ocean.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#include "Ocean.hpp"


/*********************************************************************
** Function:         Ocean()
** Description:      Constructor. Sets the label for the area.
** Parameters:       String for the label.
** Pre-Conditions:   None
** Post-Conditions:  Label is initialized
********************************************************************/
Ocean::Ocean(std::string label) : Space(label) {
}


/*********************************************************************
** Function:         special()
** Description:      The player just idles in the area using oxygen
** Parameters:       Player* player
** Pre-Conditions:   None
** Post-Conditions:  Player loses 1 oxygen
********************************************************************/
void Ocean::special(Player* player) {
  std::cout << "You rest on the surface, hoping for rescue.\n";
  player->update_oxygen(-1);
}


/*********************************************************************
** Function:         get_menu_option()
** Description:      return the option to display for this menu
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  returns a string
********************************************************************/
std::string Ocean::get_menu_option() {
  return "Wait for Rescue [1 oxygen cost]\n";
}


/*********************************************************************
** Function:         print_description()
** Description:      Handles printing the description of the area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Will print the description to user interface
********************************************************************/
void Ocean::print_description() {
  UserInterface::print_file("text/ocean.txt");
  Space::print_description();
}


/*********************************************************************
** Function:         get_type()
** Description:      Returns a string representing the type of area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  None
********************************************************************/
std::string Ocean::get_type() {
  return "Ocean";
}
