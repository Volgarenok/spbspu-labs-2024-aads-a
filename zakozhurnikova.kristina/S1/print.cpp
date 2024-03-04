#include "print.hpp"


void zakozhurnikova::printNames(const List<pair>& l)
{
  for (pair p : l)
  {
    std::cout << p.first << ' ';
  }
}

