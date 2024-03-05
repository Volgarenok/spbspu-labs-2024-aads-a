#include "print.hpp"

void zakozhurnikova::printNames(const List<pair>& l)
{
  for(auto it = l.begin(); it != l.end(); ++it)
  {
    std::cout << it->first;
    if (it + 1 != l.end())
    {
      std::cout << ' ';
    }
  }
}

void zakozhurnikova::printByIndex(const List<pair> &l)
{
  size_t maxSize = getMaxSize<size_t>(l);
  for (size_t i = 0; i < maxSize; ++i)
  {
    size_t printed = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
      if (i >= it->second.size())
      {
        continue;
      }
      std::cout << (printed++ == 0 ? "" : " ") << *(it->second.cbegin() + i);
    }
    std::cout << '\n';
  }
}
