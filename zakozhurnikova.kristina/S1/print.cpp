#include "print.hpp"


void zakozhurnikova::printNames(const List<pair>& l)
{
  for (pair p : l)
  {
    std::cout << p.first << ' ';
  }
}

void zakozhurnikova::printByIndex(const List<pair>& l)
{

  size_t maxSize = getMaxSize<size_t>(l);
  for (size_t i = 0; i < maxSize; ++i)
  {
    for (pair p : l)
    {
      if (i >= p.second.size())
      {
        continue;
      }
      std::cout << *(p.second.cbegin() + i) << ' ';
    }
    std::cout << '\n';
  }
}
