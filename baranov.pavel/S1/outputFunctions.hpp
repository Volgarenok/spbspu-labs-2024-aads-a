#ifndef OUTPUT_FUNCTIONS_HPP
#define OUTPUT_FUNCTIONS_HPP

#include <iostream>
#include "list.hpp"

namespace baranov
{
  using ds_t = List< std::pair< std::string, List< size_t > > >;
  using listOfLists = List< List< size_t > >;

  void printNames(std::ostream &, const ds_t &);
  void printList(std::ostream &, const List< size_t > &);
  void printLists(std::ostream &, const listOfLists &);

  size_t getSum(const List< size_t > &);
  void printSums(std::ostream &, const listOfLists &);
}

#endif

