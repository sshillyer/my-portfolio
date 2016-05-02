/*********************************************************************
** Program Filename: Item.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Abstract Item class. Remembers label, hint, and
**                   number of uses for items.
** Input:            None direct (abstract)
** Output:           None direct (abstract)
********************************************************************/
#include "Item.hpp"


/*********************************************************************
** Function:         Item()
** Description:      Constructor. Purposefully empty.
********************************************************************/
Item::Item() {
}


/*********************************************************************
** Function:         is_depleted()
** Description:      Returns true if number of uses is 0.
********************************************************************/
bool Item::is_depleted() {
  return (num_uses == 0);
}


/*********************************************************************
** Function:         get_label()
** Description:      Returns the label string.
********************************************************************/
std::string Item::get_label() {
  return label;
}


/*********************************************************************
** Function:         inspect()
** Description:      Prints the label, number of uses, and the hint.
********************************************************************/
void Item::inspect() {
  std::cout << "This is a " << label << " with " << num_uses << " uses available.\n";
  std::cout << "Info: " << hint << "\n";
}
