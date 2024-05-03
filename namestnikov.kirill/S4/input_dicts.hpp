#ifndef INPUT_DICTS_HPP
#define INPUT_DICTS_HPP

#include <string>
#include <map>
#include <iostream>

namespace namestnikov
{
  void inputMaps(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap);
}

#endif