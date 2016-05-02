/*********************************************************************
** Program Filename: Tournament.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/13/2015
** Description:      Class to handle a pseodogame. ALlows players to
**                   select a lineup of creatures and pit them against
**                   one another until one player is out of creatures.
** Input:            User input at keyboard.
** Output:           Simulates the tournament/game
********************************************************************/

#include "Tournament.hpp"

/*********************************************************************
** Function:         Tournament()
** Description:      Contructor. Loads menu file, init player_scores
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  creature_menu will be loaded with creature list,
**                   player_scores will all be 0.
********************************************************************/
Tournament::Tournament()
{
  creature_menu.load_menu_file("creature.menu");
  this->lineup_size = 0;
  for (int i = 0; i < 2; i++)
  {
    player_scores[i] = 0;
  }
}


/*********************************************************************
** Function:         play_tournament()
** Description:      Handles primary logic for a tournament
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Tournament will be conducted based on user input
********************************************************************/
void Tournament::play_tournament()
{
  // Set the size of lineup and populate with creatures for both players
  lineup_size = prompt_lineup_size();
  for (int player_index = 0; player_index < 2; player_index++)
    prompt_lineup(player_index);

  // Play rounds until one of the player lineups is empty (all their creatures died)
  while (!player_lineup[0].is_empty() && !player_lineup[1].is_empty())
  {
     play_round();
  }

  summary();
  // Flush the loser pile
  while (!losers.is_empty())
  {
    losers.remove();
  }
}

/*********************************************************************
** Function:         play_round()
** Description:      Handles logic for a round of the tournament
**                   between two creatures, calls subroutines
** Parameters:       None
** Pre-Conditions:   Player lineups will need to be filled with at least
**                   one creature each before calling.
** Post-Conditions:  Creatures will be removed from queues, loser added
**                   to loser stack, score updated for winner, and a
**                   summary printed to the screen.
********************************************************************/
void Tournament::play_round()
{
  // Grab the creature from the Queues
  Creature* contestants[2];
  for (int i = 0; i < 2; i++)
    contestants[i] = player_lineup[i].remove();

  // Run the combat and deal with loser and winner creatures
  Combat battle(contestants[0], contestants[1]);
  int winner_index = battle.resolve_combat();
  int loser_index = (winner_index == 0) ? 1 : 0;

  // Handle loser
  losers.add(contestants[loser_index]);
  loser_team.add(loser_index);

  // Handle winner
  revive_creature(contestants[winner_index]);
  player_lineup[winner_index].add(contestants[winner_index]);

  // Update the score
  update_score(winner_index, contestants[winner_index], contestants[loser_index]);

  // Ask user if they wish to see the updated score
  char input = 'z';
  do
  {
    std::cout << "Do you want to see current score? (Y/N)\n > ";
    std::cin >> input;
    input = toupper(input);
  } while(input != 'Y' && input != 'N');

  if (input == 'Y')
  {
    for (int i = 0; i < 2; i++)
    {
      std::cout << "Total score for Player " << (i + 1) << ": " << player_scores[i] << "\n";
    }
    std::cout << "Press enter to proceed.\n";
    std::cin.ignore(100,'\n');
    std::cin.get(); // wait for input before proceeding
  }
}

/*********************************************************************
** Function:         revive_creature()
** Description:      Restores strength for a creature; prints feedback
** Parameters:       Pointer to Creature to revive
** Pre-Conditions:   None
** Post-Conditions:  winner will have some strength restored based on
**                   specific subclass implemenation (or base if none)
********************************************************************/
void Tournament::revive_creature(Creature* winner)
{
  std::cout << winner->get_name() << " survived the battle and has a chance to rest!\n";
  int str_before = winner->check_strength();
  winner->revive();
  std::cout << "Their strength rises from " << str_before << " to ";
  std::cout << winner->check_strength() << "\n";
}

/*********************************************************************
** Function:         update_score()
** Description:      Evaluates the type of creatures and scores based
**                   on the difficulty of combat
** Parameters:       team index of the winning creatures, pointer to
**                   the two creatures that fought
** Pre-Conditions:   THe two creatuers should have done battle
** Post-Conditions:  Score will be updated for the player associated
**                   with winner_index
********************************************************************/
void Tournament::update_score(int winner_index, Creature* winner, Creature* loser)
{
  int score = 0;
  int tier[2];            // store which tier the winner and loser are in
  std::string type[2];   // store which type winner and loser are
  type[0] = winner->get_type_name();
  type[1] = loser->get_type_name();

  // set the tier for the winning (index 0) and losing (index 1) creatures
  for (int i = 0; i < 2; i++)
  {
    if (type[i] == "Goblin")
      tier[i] = 0;
    else if (type[i] == "Barbarian" || type[i] == "The Shadow")
      tier[i] = 1;
    else
      tier[i] = 2;
  }

  // winner used same tier or better tier, gets 1 pt
  if (tier[0] == tier[1] || tier[0] > tier[1])
    score = 1;
  // winner was 1 tier lower than loser, get 3 pts
  else if (tier[0] == (tier[1] - 1))
    score = 3;
  // winner was 2 tiers lower than loser, get 5 pts
  else
    score = 5;

  std::cout << "Player " << (winner_index + 1) << " earns " << score << " points!\n";
  player_scores[winner_index] += score;
}

/*********************************************************************
** Function:         summary()
** Description:      Prints summary of the tournament for user to see
** Parameters:       None
** Pre-Conditions:   Tournament should be completed.
** Post-Conditions:  Creature rankings and winning player printed to screen
********************************************************************/
void Tournament::summary()
{
  int survivors_index = (player_lineup[0].is_empty() == false) ? (0) : (1);
	std::string bar(40, '=');

  // Print the surviving creatures up to the top three
  std::cout << "\n" << bar << "\nTop three contestants are: \n" << bar << "\n";
  QueueList<Creature*> ranked_creatures;
  int rank = 1;
  while (!player_lineup[survivors_index].is_empty() && rank <=3)
  {
    Creature* survivor = player_lineup[survivors_index].remove();
    std::cout << rank << ") " << survivor->get_name() << ", a " << survivor->get_type_name() << " (team " << (survivors_index + 1) << ")\n";
    ranked_creatures.add(survivor);
    rank++;
  }

  // Grab up to 2 more from the loser pile to get top 3 (if needed)
  while (!losers.is_empty() && rank <= 3)
  {
    Creature* loser = losers.remove();
    std::cout << rank << ") " << loser->get_name() << ", a " << loser->get_type_name() << " (team " << ((survivors_index % 2) + 1) << ")\n";
    ranked_creatures.add(loser);
    rank++;
  }

  // Ask user if they wish to see the rank for the losers
  char input = 'z';
  do
  {
    std::cout << "See rankings of the rest of the creatures? (Y/N)\n > ";
    std::cin >> input;
    input = toupper(input);
  } while(input != 'Y' && input != 'N');

  if (input == 'Y')
  {
    while (!losers.is_empty())
    {
      Creature* loser = losers.remove();
      std::cout << rank << ") " << loser->get_name() << ", a " << loser->get_type_name() << " (team " << ((survivors_index % 2) + 1) << ")\n";
      ranked_creatures.add(loser);
      rank++;
    }
  }

  // Print final score and winner
  std::cout << bar << "\n";
  for (int i = 0; i < 2; i++)
  {
    std::cout << "Total score for Player " << (i + 1) << ": " << player_scores[i] << "\n";
  }
  std::cout << bar << "\n";

  if (player_scores[0] == player_scores[1])
    std::cout << "This tournament ended in a DRAW!\n";
  else
  {
    int tournament_winner = (player_scores[0] > player_scores[1]) ? 1 : 2;
    std::cout << "Player " << tournament_winner << " won!\n";
  }
  std::cout << bar << "\n";
}

/*********************************************************************
** Function:         prompt_creature_type()
** Description:      Prompts user for a type of creature.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns an int associated with a creature type
********************************************************************/
int Tournament::prompt_creature_type()
{
  int type = creature_menu.prompt_user();
  return type;
}

/*********************************************************************
** Function:         prompt_creature_name()
** Description:      Prompts user for a creature name
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Returns a string between MIN_LENGTH and MAX_LENGTH
********************************************************************/
std::string Tournament::prompt_creature_name()
{
  std::string creature_name;
  const int MIN_LENGTH = 3, MAX_LENGTH = 20;
  do
  {
    std::cout << "Enter a name for this creature ( " << MIN_LENGTH << " to " << MAX_LENGTH << " characters):\n> ";
    std::cin.ignore(10, '\n');
    std::getline(std::cin, creature_name);
  } while(creature_name.length() < MIN_LENGTH || creature_name.length() > MAX_LENGTH);

  return creature_name;
}

/*********************************************************************
** Function:         prompt_lineup()
** Description:      Iterates through menus allowing player to pick
**                   Creature type and names for their team
** Parameters:       int 0 or 1 for the index of player 1 or 2 to set
** Pre-Conditions:   lineup_size should be set prior to calling
** Post-Conditions:  The player_lineup[player_index] will be populated
********************************************************************/
void Tournament::prompt_lineup(int player_index)
{
  std::cout << "Selecting player " << (player_index + 1) << " lineup.\n";
  for (int i = 0; i < lineup_size; i++)
  {
    std::cout << "Creature " << (i + 1) << " of " << lineup_size << "\n";
    int creature_type = prompt_creature_type();
    std::string creature_name = prompt_creature_name();

    // Allocate memory for creature and assign appropriate type
    Creature* new_creature;
    switch (creature_type)
    {
      case 1: // Make barbarian
        new_creature = new Barbarian(creature_name);
        break;
      case 2: // Make BlueMen
        new_creature = new BlueMen(creature_name);
        break;
      case 3: // Make Goblin
        new_creature = new Goblin(creature_name);
        break;
      case 4: // Make ReptilePeople
        new_creature = new ReptilePeople(creature_name);
        break;
      case 5: // Make TheShadow
        new_creature = new TheShadow(creature_name);
        break;
    }

    // Add the creature to player's lineup
    player_lineup[player_index].add(new_creature);
    std::cout << "Player " << (player_index + 1) << " picked a << ";
    std::cout << new_creature->get_type_name() << " named " << new_creature->get_name() << "!\n";
  }
}


/*********************************************************************
** Function:         prompt_lineup_size()
** Description:      Prompts for size of lineup for the tournament
** Parameters:       None
** Pre-Conditions:
** Post-Conditions:  Sets this->lineup_size to value between 1 and MAX_SIZE
********************************************************************/
int Tournament::prompt_lineup_size()
{
  const int MIN_SIZE = 1, MAX_SIZE = 100;
  int size = -1;
  std::cout << "How many creatures will each team get to choose?\n";
  do
  {
    std::cout << "Pick between " << MIN_SIZE << " to " << MAX_SIZE << " for the lineup size.\n>";
    //std::cin.ignore(10, '\n');
    std::cin >> size;
  } while(size < MIN_SIZE || size > MAX_SIZE);

  return size;
}
