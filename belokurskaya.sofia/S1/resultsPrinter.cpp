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
        if (seq.at(j) != 0)
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

  List< unsigned long long > sumsList;
  
  for (size_t i = 0; i < maxLength; ++i)
  {
    unsigned long long sum = 0;
    for (size_t j = 0; j < sequences.getSize(); ++j)
    {
      const List< unsigned long long >& seq = sequences[j].getSequence();
      if (i < seq.size())
      {
        if (sum > std::numeric_limits< unsigned long long >::max() - seq.at(i))
        {
          throw std::overflow_error("Overflow");
        }
        sum += seq.at(i);
      }
    }
    sumsList.push_back(sum);
  }

  for (const auto& sum : sumsList)
  {
    out << sum << " ";
  }
  out << "\n";
}
