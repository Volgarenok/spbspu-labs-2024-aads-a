#ifndef OUTPUT_FUNCTIONS_HPP
#define OUTPUT_FUNCTIONS_HPP

#include <iostream>
#include "list.hpp"

namespace baranov
{
  using ds_t = List< std::pair< std::string, List< size_t > > >;
  using listOfLists = List< List< size_t > >;

  void printNames(std::ostream &, ds_t &);
  void printLists(std::ostream &, listOfLists &);

  size_t getSum(List< size_t > &);
  void printSums(std::ostream &, listOfLists &);
}

#endif

