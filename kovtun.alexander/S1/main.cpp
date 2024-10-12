#include <iostream>
#include <cassert>

#include "list.hpp"

int main()
{
  using pair = std::pair< std::string, kovtun::List< size_t > >;
  kovtun::List< pair > sequences;

  std::string stub;
  while(!std::cin.eof())
  {
    std::cin.clear();
    std::cin >> stub;
    if (stub.empty())
    {
      break;
    }

    kovtun::List< size_t > list;
    size_t n = 0;
    while (std::cin >> n)
    {
      list.push_back(n);
    }
    sequences.push_back({ stub, list });
  }
  
  return 0;
}
