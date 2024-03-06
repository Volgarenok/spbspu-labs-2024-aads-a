#include "inputList.hpp"
#include <iostream>

void isaychev::inputList(std::istream & in, List< std::pair< std::string, List< size_t > > > & list)
{
  std::string arg = "";
  in >> arg;
  while (!in.eof())
  {
    list.pushBack({arg, List< size_t >()});
    while (in >> arg)
    {
      try
      {
        list.front().second.pushBack(std::stoull(arg));
      }
      catch (const std::invalid_argument &)
      {
        break;
      }
    }
  }
}
