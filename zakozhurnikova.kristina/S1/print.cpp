#include "print.hpp"

void zakozhurnikova::printNames(const List<pair>& l)
{
  for( auto it = l.begin(); it != l.end(); ++it)
  {
    std::cout << it->first;
    if (it + 1 != l.end())
    {
      std::cout << ' ';
    }
  }
}

void zakozhurnikova::printByIndex(const List<pair>& l)
{

  size_t maxSize = getMaxSize<size_t>(l);
  for (size_t i = 0; i < maxSize; ++i)
  {
    for( auto it = l.begin(); it != l.end(); ++it)
    {
      if (i >= it->second.size())
      {
        continue;
      }
      std::cout << *(it->second.cbegin() + i);
      if (it + 1 != l.end())
      {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
}
