#ifndef PRINT_HPP
#define PRINT_HPP
#include <iostream>
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
}
