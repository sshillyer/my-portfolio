/*********************************************************************
** Program Filename: UserInterface.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Some ancillary user interface functions
** Input:            Some user input at console
** Output:           See specific functions
********************************************************************/
#include "UserInterface.hpp"


/*********************************************************************
** Function:         print_file() -- static
** Description:      Prints a file
** Parameters:       string for the filename
** Pre-Conditions:   Filename should exist or game crashes
** Post-Conditions:  text is printed verbatim to screen
********************************************************************/
void UserInterface::print_file(std::string filename) {
  std::fstream intro_file(filename.c_str());
  std::string line;

  if (!intro_file) {
     throw std::string("intro.txt file is missing!!!");
  }
  else {
    while (getline(intro_file, line)) {
      std::cout << line << "\n";
    }
  }
}


/*********************************************************************
** Function:         print_bar() -- static
** Description:      Prints a bar to the screen of the size passed in
** Parameters:       integer for the size of the bar
** Pre-Conditions:   None
** Post-Conditions:  Prints a bar to the screen of the size passed in
********************************************************************/
void UserInterface::print_bar(const int size) {
  std::string bar(size, '_');
  std::cout << bar << "\n";
}


/*********************************************************************
** Function:         yes_or_no() -- static
** Description:      Prompts for yes or no and continues until UserInterface
**                   enters a y or n character (upper or lower case)
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns a 'Y' or 'N'
********************************************************************/
char UserInterface::yes_or_no()
{
  char input;
  do {
    std::cout << "Y or N:\n> ";
    std::cin >> input;
    input = toupper(input);
  } while(input != 'Y' && input != 'N');
  return input;
}
