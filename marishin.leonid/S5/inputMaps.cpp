#include "inputMaps.hpp"

marishin::Tree< int, std::string > marishin::inputMaps(std::istream & in)
{
  Tree< int, std::string > myMap;
  int num = 0;
  std::string value = "";
  while (in >> num >> value)
  {
    myMap.insert(num, value);
  }
  if (!in.eof())
  {
    throw std::invalid_argument("Wrong input");
  }
  return myMap;
}
