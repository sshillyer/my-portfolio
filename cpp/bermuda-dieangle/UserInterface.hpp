/*********************************************************************
** Program Filename: UserInterface.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      Some ancillary user interface functions
** Input:            Some user input at console
** Output:           See specific functions
********************************************************************/
#ifndef SSHILLYER_USERINTERFACE_HPP
#define SSHILLYER_USERINTERFACE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

class UserInterface {
public:
  static void print_file(std::string filename);
  static void clear_screen();
  static void print_bar(const int size);
  static char yes_or_no();
};

#endif
