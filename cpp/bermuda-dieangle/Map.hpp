/*********************************************************************
** Program Filename: Map.hpp		[HEADER]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      A Map class. Links together Space* nodes and
**                   can return a starting point for the Map
** Input:            None
** Output:           Links the node per the hard-coded algorithm
********************************************************************/
#ifndef SSHILLYER_MAP_HPP
#define SSHILLYER_MAP_HPP

#include "Space.hpp"
#include "Cave.hpp"
#include "Ocean.hpp"
#include "Reef.hpp"
#include "Ship.hpp"
#include "Trench.hpp"

class Map {
private:
  Space* start;

public:
  Map();
  Space* get_start();
  void make_map();
};

#endif
