/*********************************************************************
** Program Filename: Trench.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Subclass of Space. An area for players to explore
** Input:            A label for the area
** Output:           See functions
********************************************************************/
#include "Trench.hpp"


/*********************************************************************
** Function:         Trench()
** Description:      Constructor. Sets the label for the area.
** Parameters:       String for the label.
** Pre-Conditions:   None
** Post-Conditions:  Label is initialized
********************************************************************/
Trench::Trench(std::string label) : Space(label) {
}


/*********************************************************************
** Function:         special()
** Description:      Player can try to find gear on the bodies
** Parameters:       Player* player
** Pre-Conditions:   None
** Post-Conditions:  Player can choose to swim down or not and
**                   prsented with their menu to decide what to give
**                   King. May win game or escape if they choose
********************************************************************/
void Trench::special(Player* player) {
  if (!special_used) {

    std::cout << "You get a strong feeling that amazing treasures are below!\n";
    std::cout << "If you decide to swim down, you may not have enough oxygen to make it back...\n";
    std::cout << "Do you proceed? (Y/N)\n>";
    char input = UserInterface::yes_or_no();

    if (input == 'Y') {
      this->special_used = true;
      std::cout << "You swim for a very long time, following the glow of what you think is treasure.\n";
      std::cout << "Finally, just as you're about to reach the treasure, you notice your air reserves are critical!\n";
      int oxygen_cost = -1 * (player->get_oxygen() - 1 );
      player->update_oxygen(oxygen_cost);

      std::cout << "Suddenly, a giant MerMan wearing a crown and carrying a golden Trident approaches with armed escorts.\n";
      std::cout << "\"If you wish to live, you must present me with an offering!\"\n";
      std::cout << "You can look in your inventory and use an item before your air runs out. Choose wisely!\n";
      player->view_inventory();
    }

    else if (input == 'N') {
      std::cout << "You decide not to risk it.\n";
    }
  }

  else {
    std::cout << "You've been down there already! You're not going back.\n";
  }
}


/*********************************************************************
** Function:         get_menu_option()
** Description:      return the option to display for this menu
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  returns a string
********************************************************************/
std::string Trench::get_menu_option() {
  if (!special_used) {
    return "Consider diving deeper into depths unknown\n";
  }
  else {
    return "[You've been down there already!]\n";
  }
}


/*********************************************************************
** Function:         print_description()
** Description:      Handles printing the description of the area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Will print the description to user interface
********************************************************************/
void Trench::print_description() {
  UserInterface::print_file("text/trench.txt");
  Space::print_description();
}


/*********************************************************************
** Function:         get_type()
** Description:      Returns a string representing the type of area
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  None
********************************************************************/
std::string Trench::get_type() {
  return "Trench";
}
