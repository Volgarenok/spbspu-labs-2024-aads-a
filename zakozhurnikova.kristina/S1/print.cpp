#include "print.hpp"

void zakozhurnikova::printNames(const List<pair>& l)
{
  for(auto it = l.begin(); it != l.end(); ++it)
  {
    std::cout << it->first;
    auto temp = it;
    std::advance(temp, 1);
    if (temp != l.end())
    {
      std::cout << ' ';
    }
  }
  if (l.size() != 0)
  {
    std::cout << '\n';
  }
}

void zakozhurnikova::printByIndex(const List< pair > &l)
{
  size_t maxSize = getMaxSize< size_t >(l);
  for (size_t i = 0; i < maxSize; ++i)
  {
    size_t printed = 0;
    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
      auto temp = it->second.cbegin();
      std::advance(temp, i);
      if (i >= it->second.size())
      {
        continue;
      }
      std::cout << (printed++ == 0 ? "" : " ") << *(temp);
    }
    std::cout << '\n';
  }
}
