/*********************************************************************
** Program Filename: Player.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      A player class for the game
** Input:            User input at keyboard
** Output:           Player controls player and movaes them around
**                   uses items etc.
********************************************************************/
#ifndef SSHILLYER_PLAYER_HPP
#define SSHILLYER_PLAYER_HPP

#include "Space.hpp"
#include "DivingBelt.hpp"
#include "Direction.hpp"
#include "UserInterface.hpp"
#include <iostream>

class Space; // forward declaration

class Player {
private:
  int oxygen;
  int max_oxygen;
  Space* location;
  DivingBelt belt;
  bool won_game;
  bool has_flippers;

public:
  Player();
  Player(Space* start);
  ~Player();
  int get_oxygen() const;
  void update_oxygen(const int change);
  void view_inventory();
  void print_status() const;
  void search_direction(int direction);
  void inspect_area();
  Space* current_location();
  std::string get_special_option();
  void do_special();
  void move(int direction);
  void pickup_item(Item* item);
  bool has_won();
  void wear_flippers();
  void set_win();
};

#endif
