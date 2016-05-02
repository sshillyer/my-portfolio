/*********************************************************************
** Program Filename: Menu.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/06/2015
** Description:      Highly flexible Menu class. Reads a plaintext
**                   file or takes a vector of strings and allows
**                   user to print the menu, prompt for input, and
**                   validate input without having to modify anything
**                   inside this class.
** Input:            Call with 'Menu menu_name("filename");' to
**                   instantiate with a file, or pass in a vector
**                   of strings.
** Output:           Can print menu, prompt the user, and validate
**                   input dynamically even if new items are added
**                   later at runtime or after a file/vector is read
********************************************************************/

#include "Menu.hpp"

/*********************************************************************
** Function:         Menu()   constructor
** Description:      Instantiates menu; sets the style for menu select
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Menu will be empty and have bracket style selected
********************************************************************/
Menu::Menu()
{
  brackets[0] = '[';
  brackets[1] = ']';
}


/*********************************************************************
** Function:         load_items()
** Description:      Loads a vector of items into the items vector
** Parameters:       Vector of 1 or more items
** Pre-Conditions:   argument should have 1 or more elements
** Post-Conditions:  Menu object will have 1 or more items
********************************************************************/
void Menu::load_items(std::vector<std::string> items)
{
    this->items = items;
}


/*********************************************************************
** Function:         load_menu_file()
** Description:      Loads list of items into the items vector from file
** Parameters:       Filename
** Pre-Conditions:   filename must exist in same folder and have 1 or
**                   more strings separated by newlines
** Post-Conditions:  Menu object will have 1 or more items
********************************************************************/
void Menu::load_menu_file(std::string filename)
{
  std::fstream menu_file(filename.c_str());
  std::string line;

  if (!menu_file)
  {
    std::cout << "Menu file missing!\n";
    // throw std::string("Menu file missing!");
  }
  else
  {
    getline(menu_file, line); // read first line as the header
    this->header = line;
    while (getline(menu_file, line))
    {
      this->items.push_back(line);
    }
  }
}

/*********************************************************************
** Function:         set_header()
** Description:      sets the menu header
** Parameters:       a string
** Pre-Conditions:
** Post-Conditions:
********************************************************************/

void Menu::set_header(std::string header)
{
  this->header = header;
}

/*********************************************************************
** Function:         print()
** Description:      Prints the items in the list with number to select
** Parameters:       None
** Pre-Conditions:   Must be 1+ items in list for anything to print
** Post-Conditions:  All items in Menu will print
********************************************************************/
void Menu::print()
{
  std::cout << header << "\n";
  for (int i = 0; i < this->items.size(); i++)
  {
    std::cout << brackets[0] << (i + 1) << brackets[1] << " " << this->items[i] << "\n";
  }
}


/*********************************************************************
** Function:         prompt_user()
** Description:      Gets user input from terminal until valid # picked
** Parameters:       None
** Pre-Conditions:   If no items in list, this will infinite loop!
** Post-Conditions:  A valid integer in range of the menu options
********************************************************************/
int Menu::prompt_user()
{
  int input = 0;
  do
  {
    print();
    std::cin >> input;
  } while(!is_valid(input));

  return input;
}


/*********************************************************************
** Function:         is_valid()
** Description:      Validates a number is a valid subscript for vector
**                   (with +1 offset) (range is 1 to items.size() inclusive)
** Parameters:       an int value to verify
** Pre-Conditions:   None
** Post-Conditions:  Returns true if the value is within the valid range
********************************************************************/
bool Menu::is_valid(int value)
{
  if (value >= 1 && value <= this->items.size())
    return true;
  else
    return false;
}


/*********************************************************************
** Function:         get_quit_value()
** Description:      Returns # of items in the Menu
********************************************************************/
int Menu::get_quit_value()
{
  return this->items.size();
}
