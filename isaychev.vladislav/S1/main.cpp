#include <iostream>
#include <string>
#include "list.hpp"

int main()
{
  using namespace isaychev;
  using myPair = std::pair< std::string, List< size_t > >;
  List< myPair > mainList;
  std::string arg = "";
  std::cin >> arg;
  while (!std::cin.eof())
  {
    mainList.push({arg, List< size_t >()});
    while (std::cin >> arg)
    {
      try
      {
        mainList.front().second.push(std::stoull(arg));
      }
      catch (const std::invalid_argument &)
      {
        break;
      }
    }
  }
/*  List < int > l;
  for (int i = 0; i < 4; ++i)
  {
    int a = 0;
    std::cin >> a;
    l.push(a);
  }*/
}
