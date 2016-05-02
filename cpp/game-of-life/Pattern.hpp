/*********************************************************************
** Program Filename:	Pattern.hpp		[HEADER]
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

#ifndef SSHILLYER_PATTERN_HPP
#define SSHILLYER_PATTERN_HPP

#include "Point.hpp"
#include <fstream>
#include <string>
#include <vector>

class Pattern
{
private:
	Point* points;
	int number_of_points;
	void set_points(const Point* position_list);
	bool import_pattern(const std::string);
public:
	//Pattern(const std::string file_name);
	Pattern(const Point position_list[], const int num_points);
	Pattern (const Pattern&);
	~Pattern();
	int get_number_of_points() const;
	Point get_point_at(const int index) const;

};

#endif
