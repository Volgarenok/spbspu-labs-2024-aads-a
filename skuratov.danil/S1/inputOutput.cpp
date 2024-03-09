#include <iostream>
#include <sstream>
#include <numeric>
#include <limits>
#include "inputOutput.hpp"

void skuratov::inputOutput()
{
  std::vector<Sequence> sequences;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (!line.empty())
    {
      std::istringstream iss(line);
      std::string name;
      iss >> name;
      Sequence sequence(name);
      size_t num = {};
      while (iss >> num)
      {
        sequence.numbers().push_back(num);
      }
      sequences.push_back(sequence);
    }
  }

  if (sequences.empty())
  {
    throw std::invalid_argument("Empty list");
  }

  bool first = true;
  for (const auto& seq : sequences)
  {
    if (!first)
    {
      std::cout << " ";
    }
    std::cout << seq.name();
    first = false;
  }
  std::cout << '\n';

  size_t maxSize = 1;
  for (const auto& seq : sequences)
  {
    maxSize = std::max(maxSize, seq.numbers().size());
  }

  for (size_t i = 0; i < maxSize; ++i)
  {
    bool isFirst = true;
    for (const auto& seq : sequences)
    {
      const auto& numbers = seq.numbers();
      if (i < numbers.size())
      {
        if (!isFirst)
        {
          std::cout << " ";
        }
        std::cout << numbers[i];
        isFirst = false;
      }
    }
    if (!isFirst)
    {
      std::cout << '\n';
    }
  }

  std::vector<int> column_sums(maxSize, 0);

  for (size_t i = 0; i < maxSize; ++i)
  {
    for (const auto& seq : sequences)
    {
      const auto& numbers = seq.numbers();
      if (i < numbers.size())
      {
        if (column_sums[i] <= std::numeric_limits<int>::max() - numbers[i])
        {
          column_sums[i] += numbers[i];
        }
        else
        {
          throw std::exception("Impossible to calculate");
        }
      }
    }
  }
  bool firstSeq = true;
  for (const auto& sum : column_sums)
  {
    if (!firstSeq)
    {
      std::cout << " ";
    }
    std::cout << sum;
    firstSeq = false;
  }
  std::cout << '\n';
}
