#include "inputOutput.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "list.hpp"

void skuratov::inputOutput()
{
  skuratov::List<std::pair<std::string, skuratov::List<size_t>>> sequences;

  std::string name;
  while (std::cin >> name)
  {
    skuratov::List<size_t> numbersList;
    size_t number;
    while (std::cin >> number)
    {
      numbersList.pushBack(number);
    }

    if (numbersList.empty())
    {
      throw std::invalid_argument("Empty list");
    }

    sequences.pushBack(std::make_pair(name, numbersList));
  }

  if (sequences.empty())
  {
    throw std::invalid_argument("Empty list");
  }

  bool first = true;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    if (!first)
    {
      std::cout << " ";
    }
    std::cout << sequences.get(i).first;
    first = false;
  }
  std::cout << '\n';

  size_t maxSize = 0;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    maxSize = std::max(maxSize, sequences.get(i).second.getSize());
  }

  for (size_t i = 0; i < maxSize; ++i)
  {
    bool isFirst = true;
    for (size_t j = 0; j < sequences.getSize(); ++j)
    {
      const auto& numbers = sequences.get(j).second;
      if (i < numbers.getSize())
      {
        if (!isFirst)
        {
          std::cout << " ";
        }
        std::cout << numbers.get(i);
        isFirst = false;
      }
    }
    if (!isFirst)
    {
      std::cout << '\n';
    }
  }

  skuratov::List<size_t> columnSums(maxSize, 0);

  for (size_t i = 0; i < maxSize; ++i)
  {
    for (size_t j = 0; j < sequences.getSize(); ++j)
    {
      const auto& numbers = sequences.get(j).second;
      if (i < numbers.getSize())
      {
        if (columnSums.get(i) <= std::numeric_limits<size_t>::max() - numbers.get(i))
        {
          columnSums.get(i) += numbers.get(i);
        }
        else
        {
          throw std::out_of_range("Impossible to calculate");
        }
      }
    }
  }

  bool firstSeq = true;
  for (size_t sum : columnSums)
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
