/*********************************************************************
** Program Filename:	Point.hpp	[HEADER]
** Author:            Shawn Hillyer
** Date:              09/27/2015
** Description:       Simple Point class with setters and getters
**                    to represent rows and columns. Note that this
**                    represents x as a row and y as a column (not
**                    (columns,rows) as in the Cartesian plane system)
** Input:             None
** Output:            None
********************************************************************/

#ifndef SSHILLYER_POINT_HPP
#define SSHILLYER_POINT_HPP

class Point
{
private:
	int x_coord;		// rows
	int y_coord;		// columns
public:
	Point(const int x = 0, const int y = 0);
	void set_x_coord(const int x);
	void set_y_coord(const int y);
	int get_x_coord() const;
	int get_y_coord() const;
};
#endif
