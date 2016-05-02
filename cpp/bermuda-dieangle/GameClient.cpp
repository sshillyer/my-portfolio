/*********************************************************************
** Program Filename: GameClient.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      A GameClient class to handle user input and program
**                   output
** Input:            User input at terminal to select options
** Output:           Responds to user input appropriately
********************************************************************/
#include "GameClient.hpp"


/*********************************************************************
** Function:         GameClient()
** Description:      Instantiate the client and call main_loop()
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  main_loop() will be called and GameClient will exist
********************************************************************/
GameClient::GameClient() {
	std::srand(std::time(0));

	// Load the various menu files and configure menus
	this->main_menu.load_menu_file("menu/main.menu");
	this->player_menu.load_menu_file("menu/player.menu");
	this->directions_menu.load_menu_file("menu/directions.menu");

	// Build Map and associate player to map's start, start main loop
	this->map = new Map();
	this->map->make_map();
	this->player = new Player(map->get_start());
	main_loop();
}


/*********************************************************************
** Function:         main_loop()
** Description:      Prompts for and validates user choice for next action
** Parameters:       None
** Pre-Conditions:   GameClient must exist
** Post-Conditions:  Calls other methods as appropriate
********************************************************************/
void GameClient::main_loop() {
	int menu_choice = 0;

	do 	{
		UserInterface::print_file("text/splashscreen.txt");
		// UserInterface::clear_screen(); // TODO implement clear screens and pauses
		// usleep(250000);
		menu_choice = this->main_menu.prompt_user();
		std::cin.ignore(100, '\n');

		switch (menu_choice) 		{
			case 1: // Play Game
				{
					play_game();
					std::cout << "Thanks for playing. Launch game again to play again.\n";
					menu_choice = this->main_menu.get_quit_value();
				}

				break;

			case 2: // How To Play
				{
					UserInterface::print_file("text/howtoplay.txt");
				}
				break;

			case 3: // Display Game Hint
				{
					UserInterface::print_file("text/gamehint.txt");
				}
				break;
		}
	} while (menu_choice != this->main_menu.get_quit_value());

	exit();
}


/*********************************************************************
** Function:         play_game()
** Description:      Simple algorithm to handle main game loop
** Parameters:       None
** Pre-Conditions:   Relies on the player, map, etc being "fresh"
** Post-Conditions:  Player plays until they win or lose
********************************************************************/
void GameClient::play_game() {
	// Print intro and initialize main loop of game
	UserInterface::print_bar(68);
	UserInterface::print_file("text/intro.txt");
	UserInterface::print_bar(68);

	// Prints players status, adds the location-specific menu option,
	// and prompts user to input, then removes the extra menu option at end
	while (player->get_oxygen() > 0 && !player->has_won()) {
		//UserInterface::print_bar(68);
		player->print_status();
		UserInterface::print_bar(68);
		player_menu.push_back(player->get_special_option());
		get_player_input();
		player_menu.pop_back();
		UserInterface::print_bar(68);
	}

	// Handle both win and lose conditions
	if (player->has_won()) {
		UserInterface::print_file("text/win.txt");
	}

	else {
		if (player->get_oxygen() <= 0) {
			UserInterface::print_file("text/death_oxygen.txt");
		}

		else {
			std::cout << "Not sure how you died! Must be a bug in the water...\n";
		}
	}
}

/*********************************************************************
** Function:         get_player_input()
** Description:      Handles players input during each loop
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Player input is processed
********************************************************************/
void GameClient::get_player_input() {
	int menu_choice = 0;
	const int NUM_CHOICES = 5;

	// Print the menu and take action
	do 	{
		menu_choice = this->player_menu.prompt_user();
		std::cin.ignore(100, '\n');

		switch (menu_choice) {
			case 1: // Inspect your current area
				{
					player->inspect_area();
				}
				break;
			case 2: // Search in a direction
				{
					int direction =	this->directions_menu.prompt_user();
					direction--; // fix offset because menu starts at 1
					player->search_direction(direction);
				}
				break;
			case 3: // Move
				{
					int direction =	this->directions_menu.prompt_user();
					direction--; // fix offset because menu starts at 1
					player->move(direction);
				}
				break;
			case 4: // View Inventory / Use Item
				{
					player->view_inventory();
				}
				break;
			case 5: // Special Action
				{
					player->do_special();
				}
				break;
		}
	} while (menu_choice < 1 || menu_choice > NUM_CHOICES);
}

/*********************************************************************
** Function:         exit()
** Description:      Executes any code prior to quitting the main loop
** Parameters:       none
** Pre-Conditions:   GameClient must exist
** Post-Conditions:  GameClient should stop executing code; drop into main()
********************************************************************/
void GameClient::exit() const {
	std::cout << "Exiting program.\n\n";
	std::cout << "Created by Shawn S. Hillyer\n";
	std::cout << "Shawn (dot) Hillyer (at) Gmail (dot) com\n";
	std::cout << "Date: 11/19/2015\n";
	std::cout << "Github.com/Soularpowered\n";
}


/*********************************************************************
** Function:         main()
** Description:      Entry point for program
** Parameters:       Uses none
** Pre-Conditions:   None
** Post-Conditions:  Program runs
********************************************************************/
int main(int argc, char** argv) {
	GameClient game;
	return 0;
}
