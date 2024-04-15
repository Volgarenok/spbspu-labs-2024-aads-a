#include "outputFunctions.hpp"

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

void baranov::printLists(std::ostream & output, listOfLists & lists)
{
  auto listsEnd = lists.end();
  for (auto i = lists.begin(); i != listsEnd; ++i)
  {
    auto listEnd = (*i).end();
    auto j = (*i).begin();
    output << *(j++);
    for (; j != listEnd; ++j)
    {
      output << ' ' << *j;
    }
    output << '\n';
  }
}

size_t baranov::getSum(List< size_t > & list)
{
  size_t result = 0;
  auto listEnd = list.end();
  for (auto i = list.begin(); i != listEnd; ++i)
  {
    result += *i;
  }
  return result;
}

void baranov::printSums(std::ostream & output, listOfLists & lists)
{
  auto listsEnd = lists.end();
  auto i = lists.begin();
  if (lists.empty())
  {
    output << 0 << '\n';
    return;
  }
  output << getSum(*(i++));
  for (; i != listsEnd; ++i)
  {
      output << ' ' << getSum(*i);
  }
  output << '\n';
}

