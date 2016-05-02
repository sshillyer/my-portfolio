#ifndef SSHILLYER_TRENCH_HPP
#define SSHILLYER_TRENCH_HPP

#include "Space.hpp"

class Trench : public Space {
public:
  Trench(std::string label);
  void special(Player* player);
  std::string get_menu_option();
  void print_description();
  std::string get_type();
};

#endif
