#include "input_dict.hpp"

namestnikov::Tree< int, std::string > namestnikov::inputDict(std::istream & in)
{
  Tree< int, std::string > myMap;
  int keyNumber = 0;
  std::string value = "";
  while (in >> keyNumber >> value)
  {
    myMap.insert(keyNumber, value);
  }
  if (!in.eof())
  {
    throw std::invalid_argument("Wrong input");
  }
  return myMap;
}
