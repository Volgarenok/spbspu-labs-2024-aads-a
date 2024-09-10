#include "inputList.hpp"
#include <iostream>

void isaychev::inputList(std::istream & in, List< std::pair< std::string, ullList > > & list)
{
  std::string arg = "";
  in >> arg;
  while (!in.eof())
  {
    list.push_front({arg, List< unsigned long long int >()});
    while (in >> arg)
    {
      try
      {
        list.front().second.push_front(std::stoull(arg));
      }
      catch (const std::invalid_argument &)
      {
        break;
      }
    }
  }
}
