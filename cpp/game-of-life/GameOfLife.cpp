/*********************************************************************
** Program Filename:	GameOfLife.cpp	[Implementation]
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
#include "GameOfLife.hpp"


/*********************************************************************
** Function:          GameOfLife::GameOfLife()
** Description:       Constructor
** Parameters:        rows_in: int, cols_in: int. The number of rows
**                    and columns
** Pre-Conditions:    None. Default constructor also has default values
** Post-Conditions:   Grid will be initialized with all cells set to
**                    DEAD and the # of rows/cols (within the limits
**                    defined below).
********************************************************************/
GameOfLife::GameOfLife(int rows_in, int cols_in)
{
	current_state = new Grid(rows_in, cols_in);
	next_state = new Grid(rows_in, cols_in);
	pattern_offset = Point(10, 20);
	rows = rows_in;
	cols = cols_in;
	current_generation = 0;
}


/*********************************************************************
** Function:         GameOfLife::~GameOfLife()
** Description:      Deconstructor
** Parameters:       None allowed.
** Pre-Conditions:   GameOfLife object must be deleted or fall out of scope
** Post-Conditions:  Memory for each grid is deallocated
********************************************************************/
GameOfLife::~GameOfLife()
{
	delete current_state;
	delete next_state;
}


/*********************************************************************
** Function:          GameOfLife::tick()
** Description:       Progresses to the next generation of cells and
**                    prints to the screen.
** Parameters:        None.
** Pre-Conditions:    Object must be instantiated
** Post-Conditions:   Calling will display current board status,
**                    evaluate the board (updating next_state), and
**                    make then call a swap on current_ and next_state
**                    So that the next print will show the new status
********************************************************************/
void GameOfLife::tick()
{
	display_to_console();
	run_rules();
	toggle_current_state();
	current_generation++;
}


/*********************************************************************
** Function:          GameOfLife::run_rules()
** Description:       hecks every cell of the curren_state and determines
**                    if it's dead or alive. Based on that, evaluates
**                    what its new status will be depending on the rules
**                    as specified in standard Conway's Game of Life
** Parameters:        None.
** Pre-Conditions:    Requires instantiated and initialized GameOfLIfe
**                    object. Essentially does nothing if all cells are dead
** Post-Conditions:   current_state will not be changed, but next_state will
**                    copy every cell value from current_state
********************************************************************/
void GameOfLife::run_rules()
{
	/* Main Loop that goes through each row */
	for (int i = 0; i < rows; i++)
	{
		/* Inner loop that checks each colum in row, i, of the game*/
		for (int j = 0; j < cols; j++)
		{
			/* call a count of alive nieghbors; copy current_state into next_state */
			int cell_neighbors = current_state->count_neighbors(i, j);


			bool cell_is_alive = false;
			if (current_state->get_cell_status(i, j) == ALIVE)
			{
				cell_is_alive = true;
			}

			/* Evaluate cases if cell is ALIVE */
			if (cell_is_alive)
			{
				/* Check if cell dies a lonely death */
				if (cell_neighbors == 0 || cell_neighbors == 1)
				{
					next_state->set_cell_status(i, j, DEAD);
				}
				/* Check if cell lives another generation */
				else if (cell_neighbors == 2 || cell_neighbors == 3)
				{
					next_state->set_cell_status(i, j, ALIVE);
				}
				/* Otherwise cell should die from overpopulation */
				else if (cell_neighbors > 3)
				{
					next_state->set_cell_status(i, j, DEAD);
				}
				else // it should stay alive
				{
					next_state->set_cell_status(i, j, ALIVE);
				}
			}
			/* !cell_is_alive is implied; explicit for readability */
			else if (!cell_is_alive)
			{
				if (cell_neighbors == 3)
				{
					next_state->set_cell_status(i, j, ALIVE);
				}
				else // it should stay alive
				{
					next_state->set_cell_status(i, j, DEAD);
				}
			}
		} /* End inner loop checking each cell in column*/
	} /* End main loop checking each row*/
}


/*********************************************************************
** Function:        GameOfLife::toggle_current_state()
** Description:	    Swaps current_state and next_state
** Parameters:      None.
********************************************************************/
void GameOfLife::toggle_current_state()
{
	Grid* temp_state = current_state;
	current_state = next_state;
	next_state = temp_state;
}


/*********************************************************************
** Function:          GameOfLife::display_to_console()
** Description:       Print the current game status to the screen.
**                    Purpose is to abstract the way data is output.
**                    Calls the Grid member function display_to_console()
**                    so that other information can be modularly added or
**                    removed without impacting how grid displays to console
** Parameters:        None.
** Pre-Conditions:    Requires instantiated and initialized GameOfLIfe
**                    object.
** Post-Conditions:   Screen will dispaly the Grid and whatever other
**                    pertinent information is deemed necessary.
********************************************************************/
void GameOfLife::display_to_console()
{
	/* Clear screen, print header and newline, print current_state grid */
	system("clear");
	std::cout << "Generation:\t" << current_generation << "\n";
	current_state->print_to_console();
	usleep(250000);
}


/*********************************************************************
** Function:          GameOfLife::load_pattern()
** Description:       Loads a pattern object into both states. Initializes
**                    the board completely before doing so.
** Parameters:        None.
** Pre-Conditions:    Requires a valid Pattern object for the game board
**                    size.
** Post-Conditions:   Game board will be initialized and then pattern
**                    will be loaded using the offset in data member
**                    'pattern_offset'. Current iteration also reset.
********************************************************************/
void GameOfLife::load_pattern(const Pattern& pattern)
{
	current_state->initialize();
	next_state->initialize();
	current_generation = 0;

	int total_points = pattern.get_number_of_points();

	for (int i = 0; i < total_points; i++)
	{
		Point point = pattern.get_point_at(i);
		int row = point.get_x_coord() + pattern_offset.get_x_coord();
		int col = point.get_y_coord() + pattern_offset.get_y_coord();
		current_state->set_cell_status(row, col, ALIVE);
		next_state->set_cell_status(row, col, ALIVE);
	}
}


/*********************************************************************
** Function:          GameOfLife::set_pattern_offset
** Description:       Sets the pattern offset given a point.
** Parameters:        A Point representing the offset.
** Pre-Conditions:		Requires a valid Point; defaults to top left of visible
** Post-Conditions:		pattern_offset will have a valid Point within game board
********************************************************************/
void GameOfLife::set_pattern_offset(Point offset)
{
	int x_val = offset.get_x_coord();
	int y_val = offset.get_y_coord();
	int backup_x = 10;
	int backup_y = 20;

	if (x_val < 0 || x_val > rows) // if row is too high or low
	{
		offset.set_x_coord(backup_x);
	}
	if (y_val < 0 || y_val > cols) // if row is too high or low
	{
		offset.set_y_coord(backup_y);
	}

	pattern_offset = offset;

}
