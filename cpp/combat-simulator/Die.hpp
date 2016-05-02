/*********************************************************************
** Program Filename: Die.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             10/12/2015
** Description:      Simple class to roll dice
** Input:            int to set num_sides
** Output:           Returns an int from 1 to num_sides
********************************************************************/

#ifndef SSHILLYER_DIE_HPP
#define SSHILLYER_DIE_HPP

class Die
{
protected:
	int num_sides;
	void set_num_sides(int);

public:
	Die(int sides = 6);
	virtual int roll();
};

#endif
