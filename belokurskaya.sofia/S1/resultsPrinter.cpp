#include "resultsPrinter.hpp"

#include <limits>

#include "list.hpp"

void belokurskaya::printNames(std::ostream& out, const List< std::pair< std::string, List< size_t > > >& list)
{
  auto it = list.begin();
  if (it != list.end())
  {
    out << it->first;
    ++it;
  }

  for (; it != list.end(); ++it)
  {
    out << ' ' << it->first;
  }
}

void belokurskaya::printSequence(std::ostream& output, const List< size_t >& list)
{
  if (!list.empty())
  {
    auto end = list.end();
    auto i = list.begin();
    output << *(i++);
    for (; i != end; ++i)
    {
      output << ' ' << *i;
    }
  }
}

void belokurskaya::printSequences(std::ostream& output, const List< List< size_t > >& lists)
{
  if (!lists.empty())
  {
    auto end = lists.end();
    auto i = lists.begin();
    printSequence(output, *i++);
    for (; i != end; ++i)
    {
      output << '\n';
      printSequence(output, *i);
    }
  }
}

void belokurskaya::printSums(std::ostream& output, const List< List< size_t > >& lists)
{
  size_t maxNum = std::numeric_limits< size_t >::max();
  if (lists.empty())
  {
    output << 0;
    return;
  }
  List< size_t > sums;
  for (auto i = lists.begin(); i != lists.end(); ++i)
  {
    size_t result = 0;
    auto end = i->end();
    for (auto j = i->begin(); j != end; ++j)
    {
      if (maxNum - result < *j)
      {
        throw std::overflow_error("Overflow");
      }
      result += *j;
    }
    sums.push_back(result);
  }
  printSequence(output, sums);
}
