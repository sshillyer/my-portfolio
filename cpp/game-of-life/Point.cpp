/*********************************************************************
** Program Filename:	Point.cpp	[Implementation]
** Author:            Shawn Hillyer
** Date:              09/27/2015
** Description:       Implementation of Point.hpp class methods
** Input:             Accepts integers for x and y for the constructor
**                    or individually setting points.
** Output:            A Point object or the int value of x_coord
**                    or y_coord
********************************************************************/

#include "Point.hpp"


/*********************************************************************
** Function:          Point::Point()
** Description:       Default Constructor
** Parameters:        int, int - sets the x and y private data members
** Pre-Conditions:    Requires only the int values passed in
** Post-Conditions:   A Point object will have been instantiated
********************************************************************/
Point::Point(const int x, const int y)
{
	set_x_coord(x);
	set_y_coord(y);
}


/*********************************************************************
** Function:        Point::set_x_coord()
** Description:     Updates the x_coord for the point. Validates
**                  the input is > 0 (in this grid system, negative
**                  values are outside the acceptable game world
**                  because each point is a point in an array, not
**                  a Cartesian plane)
** Parameters:      int - validated and upates the x_coord
** Pre-Conditions:  Point is instantiated or being instantiated
** Post-Conditions: x value will be updated
********************************************************************/
void Point::set_x_coord(const int x)
{
	if (x > 0)
	{
		x_coord = x;
	}
	else x_coord = 0;
}


/*********************************************************************
** Function:        Point::set_y_coord()
** Description:     Updates the y_coord for the point. Validates
**                  the input is > 0 (in this grid system, negative
**                  values are outside the acceptable game world
**                  because each point is a point in an array, not
**                  a Cartesian plane)
** Parameters:      int - validated and upates the y_coord
** Pre-Conditions:  Point is instantiated or being instantiated
** Post-Conditions: y value will be updated
********************************************************************/
void Point::set_y_coord(const int y)
{
	if (y > 0)
	{
		y_coord = y;
	}
	else y_coord = 0;

}


/*********************************************************************
** Function:         Point::get_x_coord()
** Description:      Returns the value in x_coord
** Parameters:			 None
** Pre-Conditions:   Object must exist
** Post-Conditions:  Returns x_coord
********************************************************************/
int Point::get_x_coord() const
{
	return x_coord;
}


/*********************************************************************
** Function:         Point::get_y_coord()
** Description:      Returns the value in y_coord
** Parameters:       None
** Pre-Conditions:   Object must exist
** Post-Conditions:  Returns y_coord
********************************************************************/
int Point::get_y_coord() const
{
	return y_coord;
}
