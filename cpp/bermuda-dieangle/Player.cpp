/*********************************************************************
** Program Filename: Player.hpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      A player class for the game
** Input:            User input at keyboard
** Output:           Player controls player and movaes them around
**                   uses items etc.
********************************************************************/
#include "Player.hpp"


/*********************************************************************
** Function:         Player()
** Description:      Constructor. Sets oxygen, max oxygen, and Sets
**                   their starting location.
** Parameters:       Pointer to a concrete Space subclass object
** Pre-Conditions:   Map should be instantiated with a starting pt.
** Post-Conditions:  Player should be at starting location with full
**                   oxygen
********************************************************************/
Player::Player(Space* start) {
  this->oxygen = this->max_oxygen = 200;
  this->location = start;
}


/*********************************************************************
** Function:         Player()
** Description:      Secondary constructor; obfuscated.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Sets oxygen and max oxygen vars
********************************************************************/
Player::Player() {
  this->oxygen = this->max_oxygen = 200;
}


/*********************************************************************
** Function:         ~Player()
** Description:      Remove the pointer to the map location so other
**                   destructors can delete it safely
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  location points to null
********************************************************************/
Player::~Player() {
  location = NULL;
}


/*********************************************************************
** Function:         get_oxygen()
** Description:      Returns oxygen value
********************************************************************/
int Player::get_oxygen() const {
  return oxygen;
}


/*********************************************************************
** Function:         update_oxygen()
** Description:      Increases or decreases the oxygen and prints
**                   relevant status update to player
** Parameters:       integer change
** Pre-Conditions:   None
** Post-Conditions:  Oxygen will be increased/decreased by change
********************************************************************/
void Player::update_oxygen(const int change) {
  if (change > 0) {
    std::cout << "Your Oxygen supply increases by " << change << "\n.";
  }
  else {
    if (change < 0) {
      std::cout << "You used " << -1 * change << " Oxygen.\n";
    }
  }
  this->oxygen += change;
}


/*********************************************************************
** Function:         view_inventory()
** Description:      Calls the belt's print function
********************************************************************/
void Player::view_inventory() {
  this->belt.print_items(this);
}


/*********************************************************************
** Function:         print_status()
** Description:      Prints the players status
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Prints info only
********************************************************************/
void Player::print_status() const {
  int o2_bubbles = oxygen / 5;
  std::string oxygen_bar(o2_bubbles, 'O');
  std::cout << "- Player Status -\n";
  std::cout << "Oxygen: " << oxygen << "\t\t";
  std::cout << "Location: " << location->get_label() << "\n";
  std::cout << oxygen_bar << "\n";
}


/*********************************************************************
** Function:         search_direction()
** Description:      Player searches in the direction passed in
** Parameters:       integer representing the direction
** Pre-Conditions:   Need a valid direction to search in
** Post-Conditions:  Handles the logic and updates the revealed status
**                   as appropriate
********************************************************************/
void Player::search_direction(int direction) {
  int o2_cost = -2;
  if (has_flippers == true) {
    o2_cost = o2_cost / 2;
  }

  if (!location->is_revealed(direction)) {
    location->reveal(direction);
    update_oxygen(o2_cost);
  }

  else {
    std::cout << "You've already searched in that direction.\n";
  }
}


/*********************************************************************
** Function:         inspect_area()
** Description:      Prints the player's current location's description
********************************************************************/
void Player::inspect_area() {
  location->print_description();
}


/*********************************************************************
** Function:         current_location()
** Description:      Returns the players current location as a pointer
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns the location player is at
********************************************************************/
Space* Player::current_location() {
  return location;
}


/*********************************************************************
** Function:         get_special_option()
** Description:      Gets the unique menu option for the player's current
**                   location
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns the string for this option
********************************************************************/
std::string Player::get_special_option() {
  return location->get_menu_option();
}


/*********************************************************************
** Function:         do_special()
** Description:      Player uses the current location's special ability
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Calls current location's special method
********************************************************************/
void Player::do_special() {
  location->special(this);
}


/*********************************************************************
** Function:         move()
** Description:      Moves a player and updates oxygen
** Parameters:       integer representing the direction
** Pre-Conditions:   None
** Post-Conditions:  Player's oxygen will be updated move will happen
**                   unless they haven't searched in that direction yet
********************************************************************/
void Player::move(int direction) {
  int o2_cost = -10;
  if (has_flippers == true) {
    o2_cost = o2_cost / 2;
  }
  if (location->is_revealed(direction)) {
    location = location->location_at(direction);
    location->reveal((direction + 2) % 4);
    update_oxygen(o2_cost);
  }

  else {
    std::cout << "You haven't searched in that direction yet.\n";
  }
}


/*********************************************************************
** Function:         pickup_item()
** Description:      Player attempts to pick up an item; let's them
**                   use/drop another item if their belt is full before
**                   losing ability to pick up the item for rest of game.
** Parameters:       Item* pointer
** Pre-Conditions:   Item must point to non-null or will cause exception
** Post-Conditions:  Player gets item or option to leave it behind.
********************************************************************/
void Player::pickup_item(Item* item) {
  if(belt.add_item(item)) {
    std::cout << "Added " << item->get_label() << " to Diving Belt.\n";
  }
  else {
    std::cout << "You found a " << item->get_label() << ".\n";
    std::cout << "But your belt is full. Use or drop an item to make room?\n";
    char input = UserInterface::yes_or_no();
    if (input == 'Y') {
      belt.print_items(this);
      pickup_item(item);
    }
    if (input == 'N') {
      std::cout << "You leave behind the " << item->get_label() << "\n.";
    }
  }
}


/*********************************************************************
** Function:         has_won()
** Description:      Returns true of the player's won_game is true
********************************************************************/
bool Player::has_won() {
  return won_game;
}


/*********************************************************************
** Function:         wear_flippers()
** Description:      If the player uses wear_flippers, this turns on
**                   the bool that tracks if they get the bonus
** Parameters:       None
** Pre-Conditions:   Called by the FLippers class only
** Post-Conditions:  Player has_flippers will be true
********************************************************************/
void Player::wear_flippers() {
  this->has_flippers = true;
}


/*********************************************************************
** Function:         set_win()
** Description:      Sets a flag indicating that the player as won
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  won_game will be true
********************************************************************/
void Player::set_win() {
  this->won_game = true;
}
