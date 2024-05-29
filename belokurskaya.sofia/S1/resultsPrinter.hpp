#ifndef RESULTS_PRINTER_HPP
#define RESULTS_PRINTER_HPP

#include <iostream>

#include "list.hpp"

namespace belokurskaya
{
  void printNames(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& list);
  void printSequences(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& list);
  void printSums(std::ostream& output, const List< std::pair< std::string, List< size_t > > >& list);
}

#endif