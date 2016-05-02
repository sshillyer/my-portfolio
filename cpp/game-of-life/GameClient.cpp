/*********************************************************************
** Program Filename:  GameOfLife.cpp	[Implementation]
** Author:            Shawn Hillyer
** Date:              09/27/2015
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
#include "GameOfLife.hpp"
#include <stdlib.h>
#include <iostream>
#include <string>


/* Function Prototypes */
void display_menu();
bool in_range(const int value, const int min, const int max);
void demo();
void manual_game();
void print_author();
int get_pattern_choice();
Point get_offset_choice();
int get_generations_choice();

Pattern make_oscillator();
Pattern make_glider();
Pattern make_glider_cannon();


/*********************************************************************
** Function:        main()
** Description:     Game / entry point for program
** Parameters:			None
** Pre-Conditions:		None
** Post-Conditions:		Gets and validates user input and displays
**						the Game of Life for user as appropriate
********************************************************************/
int main()
{
	std::cout << "Welcome to the Game of Life - A Zero-Player 'Game'\n";

	/* Print menu and process choice until user quits */
	const int num_menu_choices = 4;

	int menu_choice = 0;
	while (menu_choice != num_menu_choices)
	{
		/* Validate input */
		do
		{
			display_menu();
			std::cin >> menu_choice;
		} while (!in_range(menu_choice, 1, num_menu_choices));

		switch (menu_choice)
		{
		case 1:
			demo();
			break;
		case 2:
			manual_game();
			break;
		case 3:
			print_author();
			break;
		case num_menu_choices:
			print_author();
			std::cout << "Exiting program.\n\n";
			break;
		}
	}
	return 0;
}


/*********************************************************************
** Function:			display_menu()
** Description:			Prints main menu
** Parameters:			None
** Pre-Conditions:		None
** Post-Conditions:		Screen will have menu printed to console
********************************************************************/
void display_menu()
{
	std::cout << "\nWhat would you like to do?\n";
	std::cout << "1: Play a quick demo (Glider pattern)\n";
	std::cout << "2: Play a manually configured round\n";
	std::cout << "3: Print author contact info\n";
	std::cout << "4: Quit\n";
	std::cout << ">> ";
}


/*********************************************************************
** Function:			in_range()
** Description:			Checks if int 'value' is in range [min,max] inclusive
** Parameters:			int value, in min, and int max
** Pre-Conditions:		3 values to pass in
** Post-Conditions:		Returns true if min <= value <= max, false otherwise
********************************************************************/

bool in_range(const int value, const int min, const int max)
{
	if (value >= min && value <= max)
		return true;
	else
		return false;
}

void print_author()
{
	std::cout << "Created by Shawn S. Hillyer\n";
	std::cout << "Shawn (dot) Hillyer (at) Gmail (dot) com\n";
	std::cout << "Date: 09/27/2015\n";
	std::cout << "Github.com/Soularpowered\n";
}

/*********************************************************************
** Function:			demo()
** Description:			Runs a short demo of the glider pattern
** Parameters:			None
** Pre-Conditions:		None
** Post-Conditions:		Demonstration of the glider pattern prints
********************************************************************/
void demo()
{
	GameOfLife game;
	Point p1(0, 1), p2(1, 2), p3(2, 0), p4(2, 1), p5(2, 2);
	Point glider_coords[] = { p1, p2, p3, p4, p5 };
	Pattern glider(glider_coords, 5);
	game.load_pattern(glider);
	for (int i = 0; i < 6; i++)
	{
		game.tick();
		std::cout << "ITERATION " << i << "\n";
	}
}


/*********************************************************************
** Function:			manual_game()
** Description:			Prints main menu
** Parameters:			None
** Pre-Conditions:		Noneo - all processing is self-contained
** Post-Conditions:		Screen will have printed a pattern using the
**						options selected during runtime
********************************************************************/
void manual_game()
{
	/* Create the GameOfLife and Patterns used in this version of game */
	system("clear");
	GameOfLife game;
	Pattern simple_oscillator = make_oscillator();
	Pattern simple_glider = make_glider();
	Pattern glider_cannon = make_glider_cannon();

	/* Prompt for the pattern choice */
	int pattern_choice = get_pattern_choice();

	/* Prompt for starting row and column (offset) */

	game.set_pattern_offset(get_offset_choice());

	/* Prompt for number of generations to watch */
	int generations = get_generations_choice();

	/* Load and execute the selected pattern with parameters chosen above. */
	switch (pattern_choice)
	{
	case 1:		// Simple oscillator
		game.load_pattern(simple_oscillator);
		break;
	case 2:		// Simple glider
		game.load_pattern(simple_glider);
		break;
	case 3:		// Glider cannon
		game.load_pattern(glider_cannon);
		break;
	}

	/* Iterate through each generation */
	for (int i = 0; i < generations; i++)
	{
		game.tick();
	}
}

/*********************************************************************
** Function:			get_pattern_choice()
** Description:			Present users with choice of patterns and
**						validates input.
** Parameters:			None
** Pre-Conditions:		An int variable to "catch" the return value
** Post-Conditions:		Returns a valid int
********************************************************************/
int get_pattern_choice()
{
	int pattern_choice = -1;
	const int max_pattern_choices = 3;
	do
	{
		std::cout << "Which pattern would you like to see?\n";
		std::cout << "1) Simple oscillator (Suggested origin: Row = 20, Col = 40)\n";
		std::cout << "2) Simple glider (Suggested origin: Row = 10, Col = 20\n";
		std::cout << "3) Glider cannon (Suggested origin: Row = 10, Col = 20\n";
		std::cin >> pattern_choice;
	} while (!in_range(pattern_choice, 1, max_pattern_choices));

	return pattern_choice;
}

/*********************************************************************
** Function:			get_offset_choice()
** Description:			Present users with prmopts to select a row &
**						column offset and validates input for each.
** Parameters:			None
** Pre-Conditions:		A Point variable to "catch" the return value
** Post-Conditions:		Returns a valid Point
********************************************************************/
Point get_offset_choice()
{
	int starting_row = -1;
	do
	{
		std::cout << "Which row should the top-left 'cell' of the pattern start on?\n";
		std::cout << "(10-30 are visible box rows, 1-40 is valid range)\n>>";
		std::cin >> starting_row;
	} while (!in_range(starting_row, 0, 40));

	int starting_col = -1;
	do
	{
		std::cout << "Which column should the top-left 'cell' of the pattern start on?\n";
		std::cout << " (20-60 are visible box rows, 1-80 total valid range)\n>>";
		std::cin >> starting_col;
	} while (!in_range(starting_col, 1, 80));

	return Point(starting_row, starting_col);
}


/*********************************************************************
** Function:			get_generations_choice()
** Description:			Prompts user for # of generations (ticks) to
**						run the game.
** Parameters:			None
** Pre-Conditions:		An int variable to "catch" the return value
** Post-Conditions:		Return a valid int.
********************************************************************/
int get_generations_choice()
{
	int generations = -1;
	do
	{
		std::cout << "How many generations would you like to watch? (1 - 10,000)\n";
		std::cout << "Suggestions: simple oscilator < 100, glider < 100, canon < 1000\n>>";
		std::cin >> generations;
	} while (!in_range(generations, 1, 10000));

	return generations;
}


/*********************************************************************
** Function:			make_oscillator()
** Description:			Generates a oscillator Pattern object
** Parameters:			None
** Pre-Conditions:		This Pattern object can be instanted using
**						the assignment operator and calling this func.
** Post-Conditions:		Returns a Pattern that represents the oscillator
**						initial pattern seen here:

	.O.
	.O.
	.O.
**
********************************************************************/
Pattern make_oscillator()
{
	Point p1(0, 1), p2(1, 1), p3(2, 1);
	Point oscillator_coords[] = { p1, p2, p3 };
	Pattern oscillator(oscillator_coords, 3);
	return oscillator;
}


/*********************************************************************
** Function:			make_glider()
** Description:			Generates a glider Pattern object
** Parameters:			None
** Pre-Conditions:		This Pattern object can be instanted using
**						the assignment operator and calling this func.
** Post-Conditions:		Returns a Pattern that represents the glider
**						initial pattern seen here:

	.O.
	..O
	OOO
**
********************************************************************/
Pattern make_glider()
{
	Point p1(0, 1), p2(1, 2), p3(2, 0), p4(2, 1), p5(2, 2);
	Point glider_coords[] = { p1, p2, p3, p4, p5 };
	Pattern glider(glider_coords, 5);
	return glider;
}


/*********************************************************************
** Function:			make_glider_cannon()
** Description:			Generates a glider cannon Pattern object
** Parameters:			None
** Pre-Conditions:		This Pattern object can be instanted using
**						the assignment operator and calling this func.
** Post-Conditions:		Returns a Pattern that represents the glider
**						cannon initial pattern seen here:

........................O...........
......................O.O...........
............OO......OO............OO
...........O...O....OO............OO
OO........O.....O...OO..............
OO........O...O.OO....O.O...........
..........O.....O.......O...........
...........O...O....................
............OO......................

********************************************************************/
Pattern make_glider_cannon()
{
	Point p1(0, 24), p2(1, 22), p3(1, 24), p4(2, 12),
		p5(2, 13), p6(2, 20), p7(2, 21), p8(2, 34),
		p9(2, 35), p10(3, 11), p11(3, 15), p12(3, 20),
		p13(3, 21), p14(3, 34), p15(3, 35), p16(4, 0),
		p17(4, 1), p18(4, 10), p19(4, 16), p20(4, 20),
		p21(4, 21), p22(5, 0), p23(5, 1), p24(5, 10),
		p25(5, 14), p26(5, 16), p27(5, 17), p28(5, 22),
		p29(5, 24), p30(6, 10), p31(6, 16), p32(6, 24),
		p33(7, 11), p34(7, 15), p35(8, 12), p36(8, 13);

	Point glider_coords[] = { p1, p2, p3, p4, p5, p6, p7,
		p8, p9, p10, p11, p12, p13, p14, p15, p16, p17,
		p18, p19, p20, p21, p22, p23, p24, p25, p26, p27,
		p28, p29, p30, p31, p32, p33, p34, p35, p36 };
	Pattern glider(glider_coords, 36);
	return glider;
}
