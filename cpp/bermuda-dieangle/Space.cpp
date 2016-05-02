/*********************************************************************
** Program Filename: Space.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      A Space abstract class that works as a data
**                   structure. A Map can hold Space nodes s othat a
**                   player can move around. Nodes can be linked.
** Input:            Label for each Space node.
** Output:           None directly (Abstract class)
********************************************************************/
#include "Space.hpp"


/*********************************************************************
** Function:         Space()
** Description:      Constructor. Sets label and sets all nodes Parameters
**                   to null; sets revealed to false for all 4 directions
** Parameters:       String for label
** Pre-Conditions:   None
** Post-Conditions:  Variables are initialized
********************************************************************/
Space::Space(std::string label) {
  this->label = label;
  this->north = this->east = this->south = this->west = NULL;
  for (int i = 0; i < 4; i++) {
    revealed[i] = false;
  }
  this->special_used = false;
}


/*********************************************************************
** Function:         ~Space()
** Description:      Destructor. Deletes the nodes in each direction.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Deletes all node ptrs
********************************************************************/
Space::~Space() {
  if (north != NULL)
    delete north;
  if (east != NULL)
    delete east;
  if (south != NULL)
    delete south;
  if (west != NULL)
    delete west;
  north = east = south = west = NULL;
}


/*********************************************************************
** Function:         get_label()
** Description:      Returns the string label
********************************************************************/
std::string Space::get_label() {
  return label;
}


/*********************************************************************
** Function:         special_used()
** Description:      Returns true if special_used is true; otherwise false.
********************************************************************/
bool special_used() {
  return (special_used) ? true : false;
}


/*********************************************************************
** Function:         print_description()
** Description:      Prints a description of the current location and
**                   prints out what lies in each direction that The
**                   player has searched or knows about
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Prints the info described
********************************************************************/
void Space::print_description() {
  std::cout << "You are in " << get_label() << ".\n";

  for (int i = 0; i < 4; i++) {
    if (revealed[i]) {
      if (location_at(i) != NULL) {
        std::cout << Direction::get_direction(i) << ": " << location_at(i)->get_label() << "\n";
      }
      else {
        std::cout << Direction::get_direction(i) << ": No escape!\n";
      }
    }
  }
}


/*********************************************************************
** Function:         link()
** Description:      Links a Space* to another Space*
** Parameters:       integer for the direction and pointer to Space
** Pre-Conditions:   location must exist
** Post-Conditions:  Links (bidirectionally) the two Space together
********************************************************************/
void Space::link(int direction, Space* location) {
  switch (direction) {
    case 0: // North
      this->north = location;
      location->south = this;
      break;
    case 1: // East
      this->east = location;
      location->west = this;
      break;
    case 2: // South
      this->south = location;
      location->north = this;
      break;
    case 3: // West
      this->west = location;
      location->east = this;
      break;
  }
}


/*********************************************************************
** Function:         location_at()
** Description:      Returns the Space that is pointed at by this SSHILLYER_SPACE_HPP
**                   in the direction passed as argument
** Parameters:       integer representing the direction
** Pre-Conditions:   None
** Post-Conditions:  Returns a Space* or null
********************************************************************/
Space* Space::location_at(int direction) {
  switch (direction) {
    case 0: // North
      return north;
      break;
    case 1: // East
      return east;
      break;
    case 2: // south
      return south;
      break;
    case 3: // west
      return west;
      break;
    default:
      throw std::string("location_at() passed invalid value");
    }
}


/*********************************************************************
** Function:         reveal()
** Description:      Reveals a node in a specific direction
** Parameters:       Integer for a direction
** Pre-Conditions:   None
** Post-Conditions:  Updates teh revealed status of the direction
********************************************************************/
void Space::reveal(int direction) {
  if (!revealed[direction]) {
    std::cout << "To the " << Direction::get_direction(direction) << " you see...\n";
    if (location_at(direction) != NULL) {
      std::cout << location_at(direction)->get_label() << "\n";
    }
    else {
      std::cout << "... nothing in that direction!\n";
    }
    revealed[direction] = true;
  }

  else {
    std::cout << "You've already explored there.\n";
  }
}



/*********************************************************************
** Function:         is_revealed()
** Description:      Return true of the direction at (arg1) is revealed
** Parameters:       integer representing the direction
** Pre-Conditions:   None
** Post-Conditions:  Returns true or false
********************************************************************/
bool Space::is_revealed(int direction) {
  return (revealed[direction]);
}


/*********************************************************************
** Function:         get_loot()
** Description:      Returns a Pointer to an Item* or null if this
**                   space has nothing in the loot_table
** Parameters:       None
** Pre-Conditions:   random should be seeded prior to calling
** Post-Conditions:  REturns a pointer to an Item or null
********************************************************************/
Item* Space::get_loot() {
  if (loot_table.size() > 0) {
    int loot_index = std::rand() % loot_table.size();
    return loot_table[loot_index];
  }
  else {
    return NULL;
  }
}
