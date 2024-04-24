#include "resultsPrinter.hpp"

#include <iostream>

#include "list.hpp"

void belokurskaya::printNames(const SequenceVector & sequences)
{
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    std::cout << sequences[i].getName() << " ";
  }
  std::cout << "\n";
}

void belokurskaya::printSequences(const SequenceVector & sequences)
{
  size_t maxLength = 0;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    maxLength = std::max(maxLength, sequences[i].getSequence().size());
  }

  for (size_t j = 0; j < maxLength; ++j)
  {
    for (size_t i = 0; i < sequences.getSize(); ++i)
    {
      const List<int>& seq = sequences[i].getSequence();
      if (j < seq.size())
      {
        std::cout << seq.at(j) << " ";
      }
    }
    std::cout << "\n";
  }
}

void belokurskaya::printSums(const SequenceVector & sequences)
{
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    const List<int>& seq = sequences[i].getSequence();
    int sum = 0;
    for (size_t j = 0; j < seq.size(); ++j)
    {
      sum += seq.at(j);
    }
    std::cout << sum << " ";
  }
  std::cout << "\n";
}
