#include "outputFunctions.hpp"
#include "list.hpp"
#include <limits>

void baranov::printNames(std::ostream & output, ds_t & list)
{
  auto end = list.end();
  auto i = list.begin();
  output << i++->first;
  for (; i != end; ++i)
  {
    output << ' ' << i->first;
  }
  output << '\n';
}

void baranov::printList(std::ostream & output, List< size_t > & list)
{
  auto listEnd = list.end();
  auto i = list.begin();
  output << *(i++);
  for (; i != listEnd; ++i)
  {
    output << ' ' << *i;
  }
  output << '\n';
}

void baranov::printLists(std::ostream & output, listOfLists & lists)
{
  auto listsEnd = lists.end();
  for (auto i = lists.begin(); i != listsEnd; ++i)
  {
    printList(output, *i);
  }
}

size_t baranov::getSum(List< size_t > & list)
{
  size_t maxNum = std::numeric_limits< size_t >::max();
  size_t result = 0;
  auto listEnd = list.end();
  for (auto i = list.begin(); i != listEnd; ++i)
  {
    if (maxNum - result < *i)
    {
      throw std::overflow_error("Overflow");
    }
    result += *i;
  }
  return result;
}

void baranov::printSums(std::ostream & output, listOfLists & lists)
{
  auto listsEnd = lists.end();
  if (lists.empty())
  {
    output << 0 << '\n';
    return;
  }
  List< size_t > sums;
  for (auto i = lists.begin(); i != listsEnd; ++i)
  {
    sums.push_back(getSum(*i));
  }
  printList(output, sums);
}

