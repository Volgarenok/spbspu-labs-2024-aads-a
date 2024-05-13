#include "resultsPrinter.hpp"

#include <limits>

void belokurskaya::printNames(const List< SequencePair >& sequences, std::ostream& out)
{
  for (const auto& sequence : sequences)
  {
    out << sequence.getName() << " ";
  }
  out << "\n";
}

void belokurskaya::printSequences(const List< SequencePair >& sequences, std::ostream& out)
{
  size_t maxLength = 0;
  for (const auto& sequence : sequences)
  {
    maxLength = std::max(maxLength, sequence.getSequence().size());
  }

  for (size_t j = 0; j < maxLength; ++j)
  {
    for (const auto& sequence : sequences)
    {
      const List< unsigned long long >& seq = sequence.getSequence();
      if (j < seq.size() && seq.at(j) != 0)
      {
        out << seq.at(j) << " ";
      }
    }
    out << "\n";
  }
}

void belokurskaya::printSums(const List< SequencePair >& sequences, std::ostream& out)
{
  size_t maxLength = 0;
  for (const auto& sequence : sequences)
  {
    maxLength = std::max(maxLength, sequence.getSequence().size());
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
    for (const auto& sequence : sequences)
    {
      const List< unsigned long long >& seq = sequence.getSequence();
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

  if (!sumsList.empty())
  {
    out << sumsList.at(0);
    for (size_t i = 1; i < sumsList.size(); ++i)
    {
      out << " " << sumsList.at(i);
    }
  }
  out << "\n";
}
