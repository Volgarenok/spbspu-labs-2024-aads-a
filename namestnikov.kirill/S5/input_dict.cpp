#include "input_dict.hpp"

void namestnikov::inputDict(std::istream & in, Tree< int, std::string > & myMap)
{
  while (!in.eof())
  {
    in.clear();
    int keyNumber = 0;
    std::string value = "";
    while (in >> keyNumber >> value)
    {
      myMap.insert(keyNumber, value);
    }
  }
}