#include "outputList.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>

void chernov::outNames(List< namedNumberedList >& list, std::ostream& output)
{
  list.reverse();
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    it->second.reverse();
    if (it != list.begin())
    {
      output << ' ';
    }
    output << it->first;
  }
  output << '\n';
}

void chernov::outNumbers(List< namedNumberedList >& list, List< size_t >& listSums, std::ostream& output)
{
  size_t max_depth = maxDepth(list);
  for (size_t i = 0; i < max_depth; ++i)
  {
    size_t maxUll = std::numeric_limits< size_t >::max();
    size_t sum = 0;
    bool flagOfFirst = false;
    auto iter = list.begin();
    while (flagOfFirst != true && iter != list.end())
    {
      if (!(iter->second.isEmpty()))
      {
        flagOfFirst = true;
      }
      else
      {
        ++iter;
      }
    }
    auto newIter = iter;
    for (; newIter != list.end(); ++newIter)
    {
      bool flagOfEmpty = newIter->second.isEmpty();
      if (flagOfEmpty != true)
      {
        size_t temp = *(newIter->second.begin());
        if (maxUll - temp <= sum)
        {
          throw std::overflow_error("The number exceeded the limit");
        }
        else
        {
          sum += temp;
        }
        if (newIter != iter)
        {
          output << ' ';
        }
        output << temp;
        newIter->second.pop_front();
      }
    }
    output << '\n';
    listSums.push_front(sum);
  }
  listSums.reverse();
}

void chernov::outSums(List< size_t >& listSums, std::ostream& output)
{
  if (listSums.isEmpty())
  {
    throw std::logic_error("It's impossible to make up the amounts");
  }
  auto it = listSums.begin();
  output << *it;
  ++it;
  for (; it != listSums.end(); ++it)
  {
    output << ' ' << *it;
  }
  output << '\n';
}

size_t chernov::maxDepth(const List< namedNumberedList >& list)
{
  size_t max_depth = 0;
  for (auto it = list.cbegin(); it != list.cend(); ++it)
  {
    (max_depth < it->second.getSize() ? max_depth = it->second.getSize() : max_depth);
  }
  return max_depth;
}
