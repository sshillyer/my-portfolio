/*********************************************************************
** Program Filename:	Pattern.cpp		[Implementation]
** Author:            Shawn Hillyer
** Date:              09/27/2015
** Description:       Data structure that represents points on a Grid
**                    as a series of 1 or more Point objects. Can be
**                    initialized using an external ascii text file
**                    with the pattern written as lines of .'s and O's
**                    or manually passing a series of points representing
**                    the pattern.
** Input:             See constructors - file or array of Points and
**                    the number of points in the array
** Output:            Instantiated Pattern which can be used by the
**                    Game of Life and represented using a Grid object
********************************************************************/
#include "Pattern.hpp"


/*********************************************************************
** Function:          Pattern::Pattern()
** Description:       Constructor - uses a filename
** Parameters:        string: file_name
** Pre-Conditions:    file_name must exist to read from or will fail
** Post-Conditions:		A Pattern object will have been instantiated
**                    and initalized with the data from a file
********************************************************************/
/*   TODO LATER -- implement file loading system
Pattern::Pattern(const std::string file_name)
{
	number_of_points = 0; // import_pattern will update number_of_points
	import_pattern(file_name);
}
*/

/*********************************************************************
** Function:          Pattern::Pattern()
** Description:       Constructor - uses array of Points
** Parameters:        Array of Points: point_list and int: num_points
** Pre-Conditions:    Must have an array of points and # of elements
** Post-Conditions:   A Pattern object will have been instantiated
**                    and initalized with the data from an array of Points
********************************************************************/
Pattern::Pattern(const Point* point_list, const int num_points)
{
	number_of_points = num_points;
	points = new Point[num_points];
	set_points(point_list);
}


/*********************************************************************
** Function:          Pattern::~Pattern()
** Description:       Deconstructor - frees the dynamic Points[] array
** Parameters:        None allowed by compiler.
** Pre-Conditions:    Pattern object must be deleted or fall out of scope
** Post-Conditions:   Clears the memory to avoid memory leaks.
********************************************************************/
Pattern::~Pattern()
{
	delete[] points;
}

/*********************************************************************
** Function:          Pattern::Pattern(Pattern&)
** Description:       Copy constructor.
** Parameters:        Pattern& (implicitly called when object copied)
** Pre-Conditions:    A Pattern must exist to be copied.
** Post-Conditions:   Ensures a copy from function calls does not
**                    access memory deleted by local copy that is
**                    destroyed when factory function creates
********************************************************************/
Pattern::Pattern(const Pattern &obj)
{
	number_of_points = obj.number_of_points;
	points = new Point[number_of_points];
	for (int i = 0; i < number_of_points; i++)
	{
		points[i] = obj.points[i];
	}
}

/*********************************************************************
** Function:          Pattern::get_number_of_points()
** Description:       Accessor. Returns the number of points in this Pattern
** Parameters:        None required.
** Pre-Conditions:    Pattern object must be instantiated and initialized.
** Post-Conditions:   Returns the value in number_of_points
********************************************************************/
int Pattern::get_number_of_points() const
{
	return number_of_points;
}


/*********************************************************************
** Function:          Pattern::get_point_at()
** Description:       Accessor. Returns a Point object at a specific index
**                    in the array of Points, points[]
** Parameters:        int : index, the index of the Point required.
** Pre-Conditions:    object must be instantiated and initialized.
** Post-Conditions:   Returns the value in number_of_points[index]
********************************************************************/
Point Pattern::get_point_at(const int index) const
{
	if (index >= 0 || index <= number_of_points)
	{
		return points[index];
	}
	else	// should throw an exception instead but not covered yet in class
	{
		return points[0];
	}
}


/*********************************************************************
** Function:          Pattern::set_points()
** Description:       Setter. Initializes points array
** Parameters:        point_list: array of Point objects
** Pre-Conditions:		number_of_points must be initialized with correct
**                    value or data will be lost / will try to write out
**                    of array bounds
** Post-Conditions:   Every element in points[] will be initialized
********************************************************************/
void Pattern::set_points(const Point* point_list)
{
	for (int i = 0; i < number_of_points; i++)
	{
		points[i] = point_list[i];
	}
}


/*********************************************************************
** Function:          Pattern::set_points()
** Description:       Setter. Initializes the points arrayo with a
**                    series of Points
** Parameters:        point_list: array of Point objects
** Pre-Conditions:    number_of_points must be initialized with correct
**                    value or data will be lost / will try to write out
**                    of array bounds
** Post-Conditions:   Every element in points[] will be initialized and
**                    number_of_points will have the correct value
********************************************************************/
bool Pattern::import_pattern(const std::string file_name) // or call load_from_file() ??
{
	bool success = true;			// Signal if this operation fails or not
	const char ALIVE_CHAR = 'O';	// This character is the key for an ALIVE cell in GOL

	/* Set up file stream object and verify it opened, exit if failure*/
	std::fstream in_file(file_name.c_str(), std::ios::in);
	std::string current_line;
	if (!in_file)
	{
		return !success;	// Signals failure to caller
	}

	/* read lines until reach end of file. Each time an ALIVE_CHAR is found,
	 * the current x and y value is sent to a vector. the x coordinate (row) is
	 * incremented each time a newline is encountered and the y coordinate (col)
	 * is incremented each time a new char is read.
	 * Afte processing, the vector is copied into the array for quicker random
	 * access selection
	 */
	int x_val = 0;
	std::vector<Point> point_list;

	while (std::getline(in_file, current_line))
	{
		char current_char = current_line[0];

		for (int y_val = 0; y_val < static_cast<int>(current_line.length()); y_val++)
		{
			current_char = current_line[y_val];
			if (current_char == ALIVE_CHAR)
			{
				point_list.push_back(Point(x_val, y_val));
			}
		}
		x_val++; // about to read next row of the picture
	}
	/* close file then copy the vector to the array */
	in_file.close();

	number_of_points = static_cast<int>(point_list.size());
	points = new Point[number_of_points];

	for (int i = 0; i < number_of_points ; i++)
	{
		points[i] = point_list.at(i);
	}

	return success;
}
