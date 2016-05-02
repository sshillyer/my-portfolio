/*********************************************************************
** Program Filename:	GameOfLife.hpp		[HEADER]
** Author:						Shawn Hillyer
** Date:							09/27/2015
** Description:       Class to represent Conway's Game of Life.
**                    Implemented as two Grid objects to represent
**                    the state of all cells and then update the next
**                    state grid before swapping the grid that each points
**                    to.
** Input:             Will initialize with 40 rows and 80 columns.
**                    The rows and columns are passed into the Grid objects
**                    Also very boring unless a Pattern object is loaded using
**                    load_pattern() method.
** Output:            Simulates the Game of Life autonomous cell game.
**                    Printing the results of each generation to the screen
**                    allows visual representation of what's happening.
** TODO:              In future, find a way visualize graphically
**                    instead of console text.
********************************************************************/

#ifndef SSHILLYER_GAMEOFLIFE_HPP
#define SSHILLYER_GAMEOFLIFE_HPP

#include "Grid.hpp"
#include "Pattern.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

class GameOfLife
{
private:
	Grid* current_state;
	Grid* next_state;
	Point pattern_offset;
	int rows;
	int cols;
	int current_generation;
	void run_rules();
	void toggle_current_state();
	
public:
	GameOfLife(int rows_in = 40, int cols_in = 80);
	~GameOfLife();
	void tick();				// Moves game forward a round
	void display_to_console();
	void load_pattern(const Pattern&);
	void set_pattern_offset(Point);
};

#endif
