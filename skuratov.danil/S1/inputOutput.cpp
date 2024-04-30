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

void skuratov::outputAll(const List< size_t >& sequences, std::ostream& out)
{
  for (auto it1 = sequences.cbegin(); it1 != sequences.cend(); ++it1)
  {
    if (it1 != sequences.cbegin())
    {
      out << " ";
    }
    out << it1->first;
  }
  if (!sequences.empty())
  {
    out << "\n";
  }

  size_t maxSize = std::numeric_limits< size_t >::max();
  for (auto it2 = sequences.cbegin(); it2 != sequences.cend(); ++it2)
  {
    maxSize = (maxSize, it2->second.getSize());
  }

  for (size_t i = 0; i < maxSize; ++i)
  {
    bool isFirst = true;
    for (auto it3 = sequences.cbegin(); it3 != sequences.cend(); ++it3)
    {
      const auto& numbers = it3->second;
      if (i < numbers.getSize())
      {
        if (!isFirst)
        {
          out << " ";
        }
        out << numbers[i];
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
    for (auto it4 = sequences.cbegin(); it4 != sequences.cend(); ++it4)
    {
      const auto& numbers = it4->second;
      if (i < numbers.getSize())
      {
        if (columnSums.at(i) <= std::numeric_limits<size_t>::max() - numbers.at(i))
        {
          columnSums.at(i) += numbers.at(i);
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
    std::cout << columnSums.at(i);
  }
  std::cout << '\n';
}
