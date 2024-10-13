#ifndef INPUT_HPP
#define INPUT_HPP
#include <iostream>
#include <string>
#include "tree.hpp"

namespace sakovskaia
{
  Tree < std::string, Tree< size_t, std::string > > input(std::istream & input);
}

#endif
