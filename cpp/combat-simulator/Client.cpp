/*********************************************************************
** Program Filename: Client.cpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      A Client class to handle user input and program
**                   output
** Input:            User input at terminal to select options
** Output:           Responds to user iput appropriately
********************************************************************/
#include "Client.hpp"


/*********************************************************************
** Function:         Client()
** Description:      Instantiate the client and call main_loop()
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  main_loop() will be called and Client will exist
********************************************************************/
Client::Client()
{
	this->main_menu.load_menu_file("main.menu");
	main_loop();
}


/*********************************************************************
** Function:         main_loop()
** Description:      Prompts for and validates user choice for next action
** Parameters:       None
** Pre-Conditions:   Client must exist
** Post-Conditions:  Calls other methods as appropriate
********************************************************************/
void Client::main_loop()
{
	int menu_choice = 0;
	Tournament tournament;
	do
	{
		menu_choice = this->main_menu.prompt_user();
		std::cin.ignore(100, '\n');

		switch (menu_choice)
		{
		case 1:
			tournament.play_tournament();
			break;
		}
	} while (menu_choice != this->main_menu.get_quit_value());
	exit();
}


/*********************************************************************
** Function:         exit()
** Description:      Executes any code prior to quitting the main loop
** Parameters:       none
** Pre-Conditions:   Client must exist
** Post-Conditions:  Client should stop executing code; drop into main()
********************************************************************/
void Client::exit() const
{
	std::cout << "Exiting program.\n\n";
	std::cout << "Created by Shawn S. Hillyer\n";
	std::cout << "Shawn (dot) Hillyer (at) Gmail (dot) com\n";
	std::cout << "Date: 11/08/2015\n";
	std::cout << "Github.com/Soularpowered\n";
}


/*********************************************************************
** Function:         main()
** Description:      Entry point for program
** Parameters:       Uses none
** Pre-Conditions:   None
** Post-Conditions:  Program runs
********************************************************************/
int main(int argc, char** argv)
{
	Client client;
	return 0;
}
