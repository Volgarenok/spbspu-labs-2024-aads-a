#ifndef PRINT_HPP
#define PRINT_HPP
#include <iostream>
#include <limits>
#include "list.hpp"

namespace zakozhurnikova
{
  using pair = std::pair<std::string, List<size_t>>;

  template <typename T>
  size_t getMaxSize(const List<pair>& l)
  {
    T max = 0;
    for (pair p : l)
    {
      size_t size = p.second.size();
      max = std::max(max, size);
    }
    return max;
  }

  void printNames(const List<pair>& l);
  void printByIndex(const List<pair>& l);

  template <typename T>
  void printSums(const List<pair>& l)
  {
    constexpr size_t max = std::numeric_limits<size_t>::max();
    T maxSize = getMaxSize< T >(l);
    for (size_t i = 0; i < maxSize; ++i)
    {
      T sum = 0;
      for (pair p : l)
      {
        if (i >= p.second.size())
        {
          continue;
        }
        if (max - sum > *(p.second.cbegin() + i))
        {
          sum += *(p.second.cbegin() + i);
        }
        else
        {
          throw std::range_error("Failed input numbers with overflow");
        }

      }
      std::cout << sum;
      if (i < maxSize)
      {
       std::cout << ' ';
      }
    }
    if (maxSize == 0)
    {
      std::cout << "0\n";
    }
  }
}

#endif
