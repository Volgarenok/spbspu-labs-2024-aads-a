#include "inputOutput.hpp"
#include <string>
#include <limits>
#include <stdexcept>
#include <list.hpp>
#include <constIterators.hpp>

void skuratov::inputAll(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences)
{
  std::string name = "";
  while (in >> name)
  {
    if (name.empty())
    {
      break;
    }
    std::pair< std::string, List< size_t > > pair = std::make_pair(name, List< size_t >());
    sequences.pushBack(pair);

    size_t numbers = {};
    while (in >> numbers)
    {
      sequences.back().second.pushBack(numbers);
    }
    if (!in.eof())
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

  size_t maxSize = 1;
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    if (it->second.getSize() > maxSize)
    {
      maxSize = it->second.getSize();
    }
  }

  for (size_t i = 0; i < maxSize; ++i)
  {
    bool isFirst = false;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      auto numbersIt = it->second.cbegin();
      for (size_t j = 0; j < i; ++j)
      {
        if (numbersIt != it->second.cend())
        {
          ++numbersIt;
        }
      }

      if (numbersIt != it->second.cend())
      {
        if (isFirst)
        {
          out << " ";
        }

        out << *numbersIt;
        isFirst = true;
      }
    }
    if (isFirst)
    {
      out << '\n';
    }
  }

  List< size_t > columnSums = {};

  for (size_t i = 0; i < maxSize; ++i)
  {
    size_t sum = {};
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      auto numbersIt = it->second.cbegin();
      for (size_t j = 0; j < i; ++j)
      {
        if (numbersIt != it->second.cend())
        {
          ++numbersIt;
        }
      }

      if (numbersIt != it->second.cend())
      {
        if (std::numeric_limits< size_t >::max() - sum >= *numbersIt)
        {
          sum += *numbersIt;
        }
        else
        {
          throw std::overflow_error("Overflow");
        }
      }
    }
    columnSums.pushBack(sum);
  }

  for (auto it = columnSums.cbegin(); it != columnSums.cend(); ++it)
  {
    if (it != columnSums.cbegin())
    {
      out << " ";
    }
    out << *it;
  }
  out << '\n';
}
