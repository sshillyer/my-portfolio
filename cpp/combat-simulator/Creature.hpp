/*********************************************************************
** Program Filename: Creature.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      A Creature class. Has attack dice, defense dice,
**                   strength (health), and armor values. Can have
**                   a special active and a torn tendon
** Input:            None
** Output:           Base class for concrete subclasses
********************************************************************/

#ifndef SSHILLYER_CREATURE_HPP
#define SSHILLYER_CREATURE_HPP

#include "Die.hpp"
#include <string>
#include <iostream>
#include <iomanip>

class Creature
{
protected:
  std::string type_name;
  std::string name;
  int attack_dice_sides;
  int attack_dice_count;
  int defense_dice_sides;
  int defense_dice_count;
  int default_strength;
  int strength;
  int armor;
  bool special_active;
  bool torn_tendon;
public:
  Creature();
  Creature(std::string);
  ~Creature();
  virtual int attack_roll();
  int defense_roll();
  void update_strength(int);
  int check_strength();
  virtual int check_armor();
  void print_stats();
  std::string get_type_name();
  std::string get_name();
  void tear_tendon();
  bool has_special_active();
  bool has_torn_tendon();
  void toggle_special_off();
  void reset(); // MODIFICATION
  virtual void revive();
};

#endif
