/*********************************************************************
** Program Filename: DivingBelt.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Bag-like structure to hold items; provides an
**                   interface to user.
** Input:            User input and items to add
** Output:           Prints menus and allows client to manipulate
**                   the items in the bag.
********************************************************************/
#include "DivingBelt.hpp"


/*********************************************************************
** Function:         DivingBelt()
** Description:      Constructor. Sets all values to null, loads
**                   the menu file.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Fully initialized object.
********************************************************************/
DivingBelt::DivingBelt() {
  this->quantity = 0;
  this->max_size = 7;

  for (int i = 0; i < max_size; i++) {
    items[i] = NULL;
  }
  belt_menu.load_menu_file("menu/belt.menu");
}


/*********************************************************************
** Function:         ~DivingBelt()
** Description:      Destructor - frees memory from items.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Memory deallocated.
********************************************************************/
DivingBelt::~DivingBelt() {
  for (int i = 0; i < max_size; i++) {
    if (items[i] != NULL) {
      delete items[i];
      items[i] = NULL;
    }
  }
}



/*********************************************************************
** Function:         add_item()
** Description:      Add an item to the bag
** Parameters:       Pointer to Item
** Pre-Conditions:   Item must exist in memory
** Post-Conditions:  Returns true if item added, false if not.
********************************************************************/
bool DivingBelt::add_item(Item* new_item) {
  const bool SUCCESS = true;

  if (quantity < max_size) {
    items[quantity] = new_item;
    quantity++;
    return SUCCESS;
  }
  else {
    return !SUCCESS;
  }
}


/*********************************************************************
** Function:         use_item()
** Description:      Use an item in the bag at a certain index
** Parameters:       integer item_num (index), Player*
** Pre-Conditions:   Item index msut be valid.
** Post-Conditions:  Item will be used; if depleted afterwards, then
**                   removed from the belt.
********************************************************************/
void DivingBelt::use_item(int item_num, Player* player) {
  Item* item = items[item_num];
  item->use(player);
  if (item->is_depleted()) {
    remove_item(item_num);
  }
}


/*********************************************************************
** Function:         remove_item()
** Description:      Removes an item from the bag
** Parameters:       Index of an item to remove
** Pre-Conditions:   Index must refger to a non-null index
** Post-Conditions:  Item will be deleted and all other items shifted
**                   up in the list.
********************************************************************/
bool DivingBelt::remove_item(int item_num) {
  const bool SUCCESS = true;

  if (items[item_num] != NULL) {
    delete items[item_num];
    items[item_num] = NULL;

    // Shift all values up one space until "next" exceeds bound or is NULL
    int next = item_num + 1;
    while (next < max_size && items[next] != NULL) {
      items[item_num] = items[next];
      items[next] = NULL;
      ++item_num;
      ++next;
    }
    --quantity;
    return SUCCESS;
  }

  else {
    return !SUCCESS;
  }
}


/*********************************************************************
** Function:         get_quantity()
** Description:      Returns the quantity of items in the bag
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns the quantity of items in the bag
********************************************************************/
int DivingBelt::get_quantity() {
  return quantity;
}


/*********************************************************************
** Function:         print_items()
** Description:      Prints all of the items in bag and presents user
**                   with a menu of options.
** Parameters:       Player* pointer
** Pre-Conditions:   Player must exist, bag can be empty though.
** Post-Conditions:  User may inspect, use, remove item; or leave menu
********************************************************************/
void DivingBelt::print_items(Player* player) {
  UserInterface::print_bar(34);
  Menu item_menu;
  item_menu.set_header("- Diving Belt Inventory -");

  if (quantity == 0) {
    item_menu.print();
    std::cout << "You are not carrying anything.\n";
  }

  // else there must be some items, build the menu and prompt user.
  else {
    for (int i = 0; i < quantity; i++) {
      if (items[i] != NULL) {
  		    item_menu.push_back(items[i]->get_label());
      }
    }
    item_menu.print(); // prints the list of items
    UserInterface::print_bar(34);

    // prompt user what to do and handle the selection
    int input = belt_menu.prompt_user();
    switch (input) {
      case 1: // "Inspect an item"
        {
          int item_index = item_menu.prompt_user();
          --item_index; // offset by 1 because menu starts at 1
          items[item_index]->inspect();
        }
        break;
      case 2: // "Use an item"
        {
          int item_index = item_menu.prompt_user();
          --item_index; // offset by 1 because menu starts at 1
          use_item(item_index, player);
        }
        break;
      case 3: // "Drop an item"
        {
          int item_index = item_menu.prompt_user();
          --item_index; // offset by 1 because menu starts at 1
          remove_item(item_index);
        }
        break;
      case 4: // "Leave inventory"
      break;
    }
  }
}
