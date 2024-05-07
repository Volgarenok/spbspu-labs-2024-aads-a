#ifndef SEQUENCE_VECTOR_HPP
#define SEQUENCE_VECTOR_HPP

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

      SequencePair(const std::string & name, const List< unsigned long long > & sequence):
        name(name),
        sequence(sequence) {}

      const std::string & getName() const
      {
        return name;
      }

      const List< unsigned long long > & getSequence() const
      {
        return sequence;
      }
  };

  class SequenceVector
  {
    SequencePair * pairs;
    size_t size;
    size_t capacity;

    public:
      SequenceVector();
      ~SequenceVector();
      void push_back(const SequencePair & pair);
      size_t getSize() const;
      SequencePair & operator[](size_t index);
      const SequencePair & operator[](size_t index) const;
  };
}

#endif
