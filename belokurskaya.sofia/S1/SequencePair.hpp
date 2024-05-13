#ifndef SEQUENCE_PAIR_HPP
#define SEQUENCE_PAIR_HPP

#include <stdexcept>

#include "list.hpp"

namespace belokurskaya
{
  class SequencePair
  {
    std::string name;
    List< unsigned long long > sequence;

  public:
    SequencePair() {}

    SequencePair(const std::string& name, const List< unsigned long long >& sequence):
      name(name),
      sequence(sequence) {}

    const std::string& getName() const
    {
      return name;
    }

    const List< unsigned long long >& getSequence() const
    {
      return sequence;
    }
  };
}

#endif
