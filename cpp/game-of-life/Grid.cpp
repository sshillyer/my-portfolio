/*********************************************************************
** Program Filename:  Grid.cpp	[Implementation]
** Author:            Shawn Hillyer
** Date:              09/25/2015
** Description:       Implementation - represents a dynamic 2d grid
**                    with a viewable area with padding equal to half its height/width on edges
** Input:             None
** Output:            Able to print to a console current status
********************************************************************/
#include "Grid.hpp"


/*********************************************************************
** Function:         Grid::Grid()
** Description:      Constructor
** Parameters:       rows_in: int, cols_in: int.
** Pre-Conditions:   None. Default constructor also has default values
** Post-Conditions:  Grid will be initialized with all cells set to
**                   DEAD and the # of rows/cols (within the limits
**                   defined below).
********************************************************************/
Grid::Grid(const int rows_in, const int cols_in)
{
	if (rows > 40 || rows < 1)
	{
		rows = 40;
	}
	if (cols > 80 || cols < 1)
	{
		cols = 80;
	}
	else
	{
		rows = rows_in;
		cols = cols_in;
	}

	cells = new Cell*[rows];
	for (int i = 0; i < rows; i++)
	{
		cells[i] = new Cell[cols];
	}
	initialize();
}


/*********************************************************************
** Function:          Grid::~Grid()
** Description:       Deconstructor to free resources
** Parameters:        None allowed.
** Pre-Conditions:    Object must be deleted or fall out of scope.
** Post-Conditions:   All memory allocated for the cells[][] is freed.
********************************************************************/
Grid::~Grid()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] cells[i];
	}
	delete[] cells;
}


/*********************************************************************
** Function:         Grid::initialize()
** Description:      Function to set all cells to DEAD
** Parameters:       None
** Pre-Conditions:   Object must be instantiated.
** Post-Conditions:	 All values in cells[][] will be set to DEAD
********************************************************************/
void Grid::initialize()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cells[i][j] = DEAD;
		}
	}
}


/*********************************************************************
** Function:         Grid::print_to_console()
** Description:      Displays a grid to the console as series of chars
** Parameters:       None
** Pre-Conditions:   Grid must be instantiated.
** Post-Conditions:  Console should display the Grid as represented
**                   by the characters defined inside.
********************************************************************/
void Grid::print_to_console()
{
	// TODO Find a way to clear screen on UNIX and sleep etc.
	std::cout << "\n";

	/* Define the character representation for a dead and alive cell
	 * Define how much to remove from top and bottom and sides to reduce
	 * the viewable size.
	 */
	const char DEAD_CHAR = '.';
	const char ALIVE_CHAR = 'O';
	int top_bottom_padding = 10;
	int side_padding = 20;

	for (int i = top_bottom_padding; i < rows - top_bottom_padding; i++)
	{
		for (int j = side_padding; j < cols - side_padding; j++)
		{
			if (cells[i][j] == DEAD)
			{
				std::cout << DEAD_CHAR;
			}
			else	// cell is ALIVE
			{
				std::cout << ALIVE_CHAR;
			}
		}
		std::cout << "\n";
	}
}


/*********************************************************************
** Function:        Grid::count_neighbors()
** Description:     Counts how many neighbors are alive
** Parameters:      None
** Pre-Conditions:  Grid must be instantiated.
** Post-Conditions: Console should display the Grid as represented
**                  by the characters defined inside.
********************************************************************/
int Grid::count_neighbors(const int row, const int col)
{
	int neighbor_count = 0;     // accumulator

	for (int i = row - 1; i <= row+1; i++)
	{
		for (int j = col - 1; j <= col+1; j++)
		{
			/* Check the 8 surrounding cells, but not the cell we're checking */
			if (!(i == row && j == col))
			{
				if (is_alive(i, j))
				{
					neighbor_count++;
				}
			}
		}
	}
	return neighbor_count;
}


/*********************************************************************
** Function:         Grid::is_alive(int row, int col)
** Description:      Checks if a cell is alive or dead. IF cell is
**                   outside the array bounds then just assume its
**                   dead and return false.
** Parameters:       None
** Pre-Conditions:   Grid must be instantiated.
** Post-Conditions:  Console should display the Grid as represented
**                   by the characters defined inside.
********************************************************************/
bool Grid::is_alive(const int row, const int col)
{
	if (row < 0 || row >= rows ||		// Above or below the grid
		col < 0 || col >= cols)			// Left or right of the grid
	{
		return false;
	}
	else if (cells[row][col] == ALIVE)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*********************************************************************
** Function:         Grid::get_cell_status()
** Description:      Returns the status of a cell.
** Parameters:       row: int, col: int. Pass in the row and column
**                   to check
** Pre-Conditions:   Grid must be instantiated and initialized
** Post-Conditions:  Returns value of the cell (DEAD or ALIVE)
********************************************************************/
Cell Grid::get_cell_status(const int row, const int col) const
{
	return cells[row][col];
}


/*********************************************************************
** Function:         Grid::set_cell_status()
** Description:      Sets the status of a cell in this.cells[row][col];
** Parameters:       row: int, col: int, new_status: Cell. Pass in the row and column
**                   to update and the new status.
** Pre-Conditions:   Grid must be instantiated and initialized; row and col
**                   Must be within the pattern size
** Post-Conditions:  The value of the cell will be updated to new_status
********************************************************************/
void Grid::set_cell_status(const int row, const int col, Cell new_status)
{
	/* do not attempt to write to cells that are outside bounds of the Grid */
	if (row >= 0 && row < rows && col >= 0 && col < cols)
	{
		cells[row][col] = new_status;
	}
}
