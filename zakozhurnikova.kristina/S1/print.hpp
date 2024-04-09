#ifndef PRINT_HPP
#define PRINT_HPP
#include <iostream>
#include <limits>
#include "list.hpp"

namespace zakozhurnikova
{
  using pair = std::pair< std::string, List< size_t > >;

  size_t getMaxSize(const List< pair >& l);

  void printNames(const List< pair >& l);
  void printByIndex(const List< pair >& l);

  void printSums(const List< pair >& l, bool& overflow);
}

#endif
