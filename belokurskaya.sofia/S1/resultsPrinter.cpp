#include "resultsPrinter.hpp"

#include <iostream>
#include <limits>

#include "list.hpp"

void belokurskaya::printNames(const SequenceVector& sequences, std::ostream & out)
{
  for (size_t i = 0; i < sequences.getSize() - 1; ++i)
  {
    out << sequences[i].getName() << " ";
  }
  out << sequences[sequences.getSize() - 1].getName() << "\n";
}

void belokurskaya::printSequences(const SequenceVector& sequences, std::ostream & out)
{
  size_t maxLength = 0;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    maxLength = std::max(maxLength, sequences[i].getSequence().size());
  }

  for (size_t j = 0; j < maxLength - 1; ++j)
  {
    for (size_t i = 0; i < sequences.getSize(); ++i)
    {
      const List< int > & seq = sequences[i].getSequence();
      if (j < seq.size())
      {
        out << seq.at(j) << " ";
      }
      out << seq.at(maxLength - 1);
    }
    out << "\n";
  }
}

void belokurskaya::printSums(const SequenceVector& sequences, std::ostream & out)
{
  size_t maxLength = 0;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    maxLength = std::max(maxLength, sequences[i].getSequence().size());
  }

  int* sums = new int[maxLength] {};
  if (sums == nullptr)
  {
    std::cerr << "Failed to allocate memory\n";
    return;
  }
  for (size_t i = 0; i < maxLength; ++i)
  {
    sums[i] = 0;
  }

  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    const List< int > & seq = sequences[i].getSequence();
    for (size_t j = 0; j < maxLength; ++j)
    {
      int max = std::numeric_limits< int >::max() - seq.at(j);
      if (sums[j] > max - seq.at(j))
      {
        delete[] sums;
        throw std::overflow_error("Overflow");
      }
      sums[j] += seq.at(j);
    }
  }

  for (size_t i = 0; i < maxLength - 1; ++i)
  {
    out << sums[i] << " ";
  }
  out << sums[maxLength - 1] << "\n";

  delete[] sums;
}
