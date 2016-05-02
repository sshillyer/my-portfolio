/*********************************************************************
** Program Filename: Tournament.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Class to handle a pseodogame. ALlows players to
**                   select a lineup of creatures and pit them against
**                   one another until one player is out of creatures.
** Input:            User input at keyboard.
** Output:           Simulates the tournament/game
********************************************************************/

#ifndef SSHILLYER_TOURNAMENT_HPP
#define SSHILLYER_TOURNAMENT_HPP

#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Combat.hpp"
#include "Creature.hpp"
#include "Goblin.hpp"
#include "Menu.hpp"
#include "QueueList.hpp"
#include "ReptilePeople.hpp"
#include "StackList.hpp"
#include "TheShadow.hpp"
#include <vector>

class Tournament
{
private:
  // Data
  int lineup_size;
  Menu creature_menu;
  QueueList<Creature*> player_lineup[2]; // make vector for type safety? probably not...
  StackList<Creature*> losers;
  StackList<int> loser_team;
  int player_scores[2];

  // Methods
  void play_round();
  void revive_creature(Creature*);
  void update_score(int, Creature*, Creature*);
  void summary();
  int prompt_lineup_size();

public:
  Tournament();
  int prompt_creature_type();
  std::string prompt_creature_name();
  void prompt_lineup(int player_index);
  void play_tournament();
};

#endif
