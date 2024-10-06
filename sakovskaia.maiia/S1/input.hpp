#ifndef INPUT_HPP
#define INPUT_HPP
#include <iostream>
#include <string>
#include <iosfwd>
#include "list.hpp"
namespace sakovskaia
{
  using ullList = List< unsigned long long int >;
  void input(std::istream & input, List< std::pair< std::string, ullList > > & list);
}
#endif
