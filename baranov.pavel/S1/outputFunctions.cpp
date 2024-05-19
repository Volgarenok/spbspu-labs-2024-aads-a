#include "outputFunctions.hpp"
#include <limits>
#include <cassert>
#include "list.hpp"

void baranov::printNames(std::ostream & output, const ds_t & sequences)
{
  assert(!sequences.empty());
  auto end = sequences.cend();
  auto i = sequences.cbegin();
  output << i++->first;
  for (; i != end; ++i)
  {
    output << ' ' << i->first;
  }
}

void baranov::printList(std::ostream & output, const List< size_t > & list)
{
  assert(!list.empty());
  auto end = list.cend();
  auto i = list.cbegin();
  output << *(i++);
  for (; i != end; ++i)
  {
    output << ' ' << *i;
  }
}

void baranov::printLists(std::ostream & output, const listOfLists & lists)
{
  assert(!lists.empty());
  auto end = lists.cend();
  auto i = lists.cbegin();
  printList(output, *i++);
  for (; i != end; ++i)
  {
    output << '\n';
    printList(output, *i);
  }
}

size_t baranov::getSum(const List< size_t > & list)
{
  size_t maxNum = std::numeric_limits< size_t >::max();
  size_t result = 0;
  auto end = list.cend();
  for (auto i = list.cbegin(); i != end; ++i)
  {
    if (maxNum - result < *i)
    {
      throw std::overflow_error("Overflow");
    }
    result += *i;
  }
  return result;
}

void baranov::printSums(std::ostream & output, const listOfLists & lists)
{
  auto end = lists.cend();
  if (lists.empty())
  {
    output << 0;
    return;
  }
  List< size_t > sums;
  for (auto i = lists.cbegin(); i != end; ++i)
  {
    sums.push_back(getSum(*i));
  }
  printList(output, sums);
}

