#include "SequenceVector.hpp"

belokurskaya::SequenceVector::SequenceVector():
  pairs(new SequencePair[10000]),
  size(0),
  capacity(10000) {}

belokurskaya::SequenceVector::~SequenceVector()
{
  delete[] pairs;
}

void belokurskaya::SequenceVector::push_back(const SequencePair & pair)
{
  if (size < capacity)
  {
    pairs[size++] = pair;
  }
  else
  {
    capacity *= 2;
    SequencePair * newPairs = new SequencePair[capacity];
    for (size_t i = 0; i < size; ++i)
    {
      newPairs[i] = pairs[i];
    }
    delete[] pairs;
    pairs = newPairs;
    if (size < capacity)
    {
      pairs[size++] = pair;
    }
    else
    {
      throw std::runtime_error("Array capacity exceeded");
    }
  }
}

size_t belokurskaya::SequenceVector::getSize() const
{
  return size;
}

belokurskaya::SequencePair & belokurskaya::SequenceVector::operator[](size_t index)
{
  if (index >= size)
  {
    throw std::out_of_range("Index out of range");
  }
  return pairs[index];
}

const belokurskaya::SequencePair & belokurskaya::SequenceVector::operator[](size_t index) const
{
  if (index >= size)
  {
    throw std::out_of_range("Index out of range");
  }
  return pairs[index];
}
