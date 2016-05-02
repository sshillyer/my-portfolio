/*********************************************************************
** Program Filename: Map.cpp		[IMPLEMENTATION]
** Author:           Shawn Hillyer
** Date:             11/28/2015
** Description:      A Map class. Links together Space* nodes and
**                   can return a starting point for the Map
** Input:            None
** Output:           Links the node per the hard-coded algorithm
********************************************************************/
#include "Map.hpp"


/*********************************************************************
** Function:         Map()
** Description:      Constructor. Sets the starting point to null.
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  Initialize start to null
********************************************************************/
Map::Map() {
  this->start = NULL;
}


/*********************************************************************
** Function:         get_start()
** Description:      Returns the starting point of the map
** Parameters:       None
********************************************************************/
Space* Map::get_start() {
  return this->start;
}


/*********************************************************************
** Function:         make_map()
** Description:      Creates all of the concrete Space subclasses and
**                   links them together and sets the starting point
** Parameters:       None
** Pre-Conditions:   None
** Post-Conditions:  All nodes will be linked per the map below
********************************************************************/
void Map::make_map() {
  Ocean* o1 = new Ocean("Open Water #1");
  Space* starting_node = o1;
  this->start = starting_node;

  Ocean* o2 = new Ocean("Open Water #2");
  Ocean* o3 = new Ocean("Open Water #3");
  Ocean* o4 = new Ocean("Open Water #4");
  Ocean* o5 = new Ocean("Open Water #5");
  Ocean* o6 = new Ocean("Open Water #6");
  Ocean* o7 = new Ocean("Open Water #7");
  Ocean* o8 = new Ocean("Open Water #8");

  Cave* c1 = new Cave("Underwater Cave #1");
  Cave* c2 = new Cave("Underwater Cave #2");
	Cave* c3 = new Cave("Underwater Cave #3");
  Cave* c4 = new Cave("Underwater Cave #4");
  Cave* c5 = new Cave("Underwater Cave #5");

  Reef* r1 = new Reef("Dangerous Reef #1");
  Reef* r2 = new Reef("Dangerous Reef #2");
  Reef* r3 = new Reef("Dangerous Reef #3");
  Reef* r4 = new Reef("Dangerous Reef #4");

  Ship* s1 = new Ship("Wrecked Pirate Ship");
  Ship* s2 = new Ship("Wrecked Submarine");
  Ship* s3 = new Ship("Capsized Treasure Hunter Ship");
  Ship* s4 = new Ship("Oceanic Flight 815");

  Trench* t1 = new Trench("Abyssal Trench #1");
  Trench* t2 = new Trench("Abyssal Trench #2");
  Trench* t3 = new Trench("Abyssal Trench #3");
  Trench* t4 = new Trench("Abyssal Trench #4");
  Trench* t5 = new Trench("Abyssal Trench #5");
  Trench* t6 = new Trench("Abyssal Trench #6");
  Trench* t7 = new Trench("Abyssal Trench #7");

  t1->link(1, t2);
  t1->link(2, r4);
  t2->link(1, t3);
  t2->link(2, c4);
  t3->link(1, t4);
  t4->link(1, t5);
  t5->link(1, t6);
  t6->link(1, t7);
  s3->link(3, c5);
  s3->link(0, t4);
  c4->link(1, c5);
  c4->link(3, r4);
  o8->link(0, t5);
  o8->link(1, s4);
  o8->link(2, r3);
  o8->link(3, s3);
  s4->link(0, t6);
  s2->link(0, r4);
  s2->link(1, o6);
  s2->link(2, o4);
  o2->link(0, o4);
  o2->link(2, o1);
  o1->link(2, c3);
  o1->link(1, o3);
  c1->link(1, c2);
  c1->link(2, o3);
  c1->link(3, o2);
  c2->link(0, s1);
  o5->link(3, o4);
  o5->link(0, o6);
  o5->link(1, s1);
  s1->link(1, r1);
  o7->link(1, r2);
  o7->link(2, s1);
  o7->link(3, o6);
  r2->link(0, s3);
  r2->link(2, r1);
}
