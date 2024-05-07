#include "resultsPrinter.hpp"

#include <iostream>
#include <limits>

#include "list.hpp"

void belokurskaya::printNames(const SequenceVector& sequences, std::ostream& out)
{
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    out << sequences[i].getName();
    if (i < sequences.getSize() - 1)
    {
      out << " ";
    }
  }
  if (sequences.getSize() > 0)
  {
    out << "\n";
  }
}

void belokurskaya::printSequences(const SequenceVector& sequences, std::ostream& out)
{
  size_t maxLength = 0;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    maxLength = std::max(maxLength, sequences[i].getSequence().size());
  }

  for (size_t j = 0; j < maxLength; ++j)
  {
    bool hasOutput = false;
    for (size_t i = 0; i < sequences.getSize(); ++i)
    {
      const List< unsigned long long >& seq = sequences[i].getSequence();
      if (j < seq.size())
      {
        if (seq.at(j) != -1)
        {
          if (hasOutput)
          {
            out << " ";
          }
          out << seq.at(j);
          hasOutput = true;
        }
      }
    }
    if (hasOutput)
    {
      out << "\n";
    }
  }
}

void belokurskaya::printSums(const SequenceVector& sequences, std::ostream& out)
{
  size_t maxLength = 0;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    maxLength = std::max(maxLength, sequences[i].getSequence().size());
  }
  if (maxLength == 0)
  {
    out << "0\n";
    return;
  }
  unsigned long long* sums = new unsigned long long[maxLength] {};
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
    const List< unsigned long long >& seq = sequences[i].getSequence();
    for (size_t j = 0; j < seq.size(); ++j)
    {
      if (j < maxLength)
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
  }

  for (size_t i = 0; i < maxLength; ++i)
  {
    out << sums[i];
    if (i < maxLength - 1)
    {
      out << " ";
    }
  }
  out << "\n";

  delete[] sums;
}
