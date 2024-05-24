#include "resultsPrinter.hpp"

#include <limits>

#include "list.hpp"

void belokurskaya::printNames(std::ostream& out, const List < std::pair< std::string, List< size_t > > >& list)
{
  auto end = list.end();
  auto i = list.begin();
  out << i++->first;
  for (; i != end; ++i)
  {
    out << ' ' << i->first;
  }
}

void belokurskaya::printSequences(std::ostream& out, const List< size_t >& list)
{
  auto endOfList = list.end();
  auto i = list.begin();

  while (i != endOfList)
  {
    auto subList = *i;
    auto subEndOfList = subList.end();
    auto subListIterator = subList.begin();

    out << *(subListIterator++);
    for (; subListIterator != subEndOfList; ++subListIterator)
    {
      out << ' ' << *subListIterator;
    }
    ++i;
  }
}

void belokurskaya::printSums(std::ostream& output, const List< List< size_t > >& lists)
{
  size_t maxNum = std::numeric_limits< size_t >::max();
  List< size_t > sums;

  if (lists.empty())
  {
    output << 0 << '\n';
    return;
  }

  for (const auto& list : lists)
  {
    size_t sum = 0;
    for (const auto& num : list)
    {
      if (maxNum - sum < num)
      {
        throw std::overflow_error("Overflow");
      }
      sum += num;
    }
    sums.push_back(sum);
  }

  auto sumsEnd = sums.end();
  auto i = sums.begin();

  output << *(i++);
  for (; i != sumsEnd; ++i)
  {
    output << ' ' << *i;
  }
}
