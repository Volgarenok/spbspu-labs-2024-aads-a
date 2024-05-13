#ifndef RESULTS_PRINTER_HPP
#define RESULTS_PRINTER_HPP

#include <iostream>

#include "SequencePair.hpp"

namespace belokurskaya
{
  void printNames(const List< SequencePair >& sequences, std::ostream& out);
  void printSequences(const List< SequencePair >& sequences, std::ostream& out);
  void printSums(const List< SequencePair >& sequences, std::ostream& out);
}

#endif
