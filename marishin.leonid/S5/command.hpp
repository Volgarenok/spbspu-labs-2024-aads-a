#ifndef COMAND_HPP
#define COMAND_HPP

#include <string>
#include <binarySearchTree.hpp>

namespace marishin
{
  void ascending(int & result, std::string & line, Tree< int, std::string > & map);
  void descending(int & result, std::string & line, Tree< int, std::string > & map);
  void breadth(int & result, std::string & line, Tree< int, std::string > & map);
}

#endif
