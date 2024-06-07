#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <string>
#include <tree.hpp>

namespace namestnikov
{
  void ascending(int & result, std::string & line, Tree< int, std::string > & map);
  void descending(int & result, std::string & line, Tree< int, std::string > & map);
  void breadth(int & result, std::string & line, Tree< int, std::string > & map);
}

#endif
