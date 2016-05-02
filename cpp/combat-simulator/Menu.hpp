/*********************************************************************
** Program Filename: Menu.hpp		[HEADER]
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

#ifndef SSHILLYER_MENU_HPP
#define SSHILLYER_MENU_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Menu
{
private:
  std::vector<std::string> items;
  char brackets[2];
  std::string header;
public:
  Menu();
  void load_items(std::vector<std::string> items);
  void load_menu_file(std::string filename);
  void set_header(std::string);
  void print();
  int prompt_user();
  bool is_valid(int value);
  int get_quit_value();
};

#endif
