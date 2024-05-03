#include "inputOutput.hpp"
#include <string>
#include <limits>
#include <stdexcept>
#include "list.hpp"
#include "constIterators.hpp"

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
    std::pair< std::string, List< size_t > > pair = std::make_pair(name, List< size_t >());
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

void skuratov::outputAll(const List< std::pair< std::string, List< size_t > > >& sequences, std::ostream& out)
{
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    if (it != sequences.cbegin())
    {
      out << " ";
    }
    out << it->first;
  }
  if (!sequences.empty())
  {
    out << "\n";
  }

  size_t maxSize = std::numeric_limits< size_t >::max();
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    if (it->second.getSize() > maxSize)
    {
      maxSize = it->second.getSize();
    }
  }

  for (size_t i = 0; i < maxSize; ++i)
  {
    bool isFirst = true;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      auto numbers = it->second;
      auto numbersIt = numbers.cbegin();
      std::advance(numbersIt, i);
      if (numbersIt != numbers.cend())
      {
        if (!isFirst)
        {
          out << " ";
        }
        out << *numbersIt;
        isFirst = false;
      }
    }
    if (!isFirst)
    {
      out << '\n';
    }
  }

  List< size_t > columnSums = {};

  for (size_t i = 0; i < maxSize; ++i)
  {
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      auto numbers = it->second;
      auto numbersIt = numbers.cbegin();
      std::advance(numbersIt, i);
      if (numbersIt != numbers.cend())
      {
        if (columnSums.getSize() <= i)
        {
          columnSums.pushBack(*numbersIt);
        }
        else
        {
          if (columnSums[i] <= std::numeric_limits<size_t>::max() - *numbersIt)
          {
            columnSums[i] += *numbersIt;
          }
          else
          {
            throw std::out_of_range("Impossible to calculate");
          }
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
