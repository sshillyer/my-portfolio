/*********************************************************************
** Program Filename:	Grid.hpp		[HEADER]
** Author:            Shawn Hillyer
** Date:              09/25/2015
** Description:       Implementation - represents a dynamic 2d grid
**                    with a viewable area with padding equal to half its height/width on edges
** Input:             None
** Output:            Able to print to a console current status
********************************************************************/

#ifndef SSHILLYER_GRID_HPP
#define SSHILLYER_GRID_HPP

#include "Cell.hpp"
#include <iostream>

class Grid
{
private:
	Cell** cells;
	int rows;
	int cols;
	bool is_alive(const int row, const int col);
public:
	Grid(const int rows_in = 40, const int cols_in = 80);
	~Grid();
	void initialize();
	void print_to_console();
	int count_neighbors(const int row, const int col);
	Cell get_cell_status(const int row, const int col) const;
	void set_cell_status(const int row, const int col, Cell new_status);
};

#endif
