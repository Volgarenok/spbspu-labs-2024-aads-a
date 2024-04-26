#ifndef SEQUENCE_PRINTER_HPP
#define SEQUENCE_PRINTER_HPP

#include "SequenceVector.hpp"

namespace belokurskaya
{
  void printNames(const SequenceVector & sequences, std::ostream & out);
  void printSequences(const SequenceVector & sequences, std::ostream & out);
  void printSums(const SequenceVector & sequences, std::ostream & out);
}

#endif
