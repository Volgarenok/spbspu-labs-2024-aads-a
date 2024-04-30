#include "inputOutput.hpp"
#include <string>
#include <limits>
#include <stdexcept>
#include "list.hpp"

void skuratov::inputAll(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences)
{
  std::string name = "";
  while (in)
  {
    in >> name;
    if (name.empty())
    {
      throw std::invalid_argument("Empty list");
      break;
    }
    std::pair<std::string, List<size_t>> pair = std::make_pair(name, List<size_t>());
    sequences.pushBack(pair);

    size_t numbers = {};
    while (in >> numbers)
    {
      sequences.back().second.pushBack(numbers);
    }
    if (!in)
    {
      in.clear();
    }
  }
}

/*
{
  bool first = true;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    if (!first)
    {
      std::cout << " ";
    }
    std::cout << sequences[i].first;
    first = false;
  }
  std::cout << '\n';

  size_t maxSize = 0;
  for (size_t i = 0; i < sequences.getSize(); ++i)
  {
    maxSize = std::max(maxSize, sequences[i].second.getSize());
  }

  for (size_t i = 0; i < maxSize; ++i)
  {
    bool isFirst = true;
    for (size_t j = 0; j < sequences.getSize(); ++j)
    {
      const auto& numbers = sequences[j].second;
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

  for (size_t i = 0; i < maxSize; ++i)
  {
    for (size_t j = 0; j < sequences.getSize(); ++j)
    {
      const auto& numbers = sequences[j].second;
      if (i < numbers.getSize())
      {
        if (columnSums[i] <= std::numeric_limits<size_t>::max() - numbers.get(i))
        {
          columnSums[i] += numbers.get(i);
        }
        else
        {
          throw std::out_of_range("Impossible to calculate");
        }
      }
    }
  }

  for (size_t i = 0; i < columnSums.getSize(); ++i)
  {
    if (i != 0)
    {
      std::cout << " ";
    }
    std::cout << columnSums[i];
  }
  std::cout << '\n';
}
*/
