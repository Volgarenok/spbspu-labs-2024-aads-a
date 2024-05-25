#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iostream>
#include <tree.hpp>


namespace namestnikov
{
  void print(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap, std::ostream & out);
  void makeIntersect(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap);
  void makeUnion(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap);
  void makeComplement(std::istream & in, Tree< std::string, Tree< size_t, std::string > > & myMap);
}

#endif
