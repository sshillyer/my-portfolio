/*********************************************************************
** Program Filename: Client.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      A Client class to handle user input and program
**                   output for a SearchSort object
** Input:            User input at terminal to select options
** Output:           Prints values to demonstrate searching/sorting
********************************************************************/
#ifndef SSHILLYER_CLIENT_HPP
#define SSHILLYER_CLIENT_HPP

#include "Menu.hpp"
#include "Tournament.hpp"
#include <iostream>
#include <vector>

class Client
{
private:
	Menu main_menu;

public:
	Client();
	void main_loop();
	void exit() const;
};

#endif
