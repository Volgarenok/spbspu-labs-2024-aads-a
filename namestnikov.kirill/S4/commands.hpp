#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <string>
#include <iostream>


namespace namestnikov
{
  void print(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap, std::ostream & out);
  void makeIntersect(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap);
  void makeUnion(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap);
  void makeComplement(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap);
}

#endif