/*********************************************************************
** Program Filename: GameClient.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      A GameClient class to handle user input and program
**                   output
** Input:            User input at terminal to select options
** Output:           Responds to user input appropriately
********************************************************************/
#ifndef SSHILLYER_GAMECLIENT_HPP
#define SSHILLYER_GAMECLIENT_HPP

#include "Cave.hpp"
#include "Direction.hpp"
#include "DivingBelt.hpp"
#include "Flare.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "Ocean.hpp"
#include "Player.hpp"
#include "Reef.hpp"
#include "Ship.hpp"
#include "Space.hpp"
#include "Trench.hpp"
#include "UserInterface.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

class GameClient {
protected:
	Menu main_menu;
	Menu player_menu;
	Menu directions_menu;
	Map* map;
	Player* player;

public:
	GameClient();
	void main_loop();
	void play_game();
	void get_player_input();
	void exit() const;
};

#endif
