#include "outputFunctions.hpp"

void baranov::printNames(std::ostream & output, ds_t & list)
{
  auto end = list.end();
  for (auto i = list.begin(); i != end; ++i)
  {
    output << i->first;
    output << ' ';
  }
  output << '\n';
}

void baranov::printLists(std::ostream & output, listOfLists & lists)
{
  auto listsEnd = lists.end();
  for (auto i = lists.begin(); i != listsEnd; ++i)
  {
    auto listEnd = (*i).end();
    for (auto j = (*i).begin(); j != listEnd; ++j)
    {
      output << *j << ' ';
    }
    output << '\n';
  }
}

void baranov::printSums(std::ostream & output, listOfLists & lists)
{
  auto listsEnd = lists.end();
  for (auto i = lists.begin(); i != listsEnd; ++i)
  {
    size_t result = 0;
    auto listEnd = (*i).end();
    for (auto j = (*i).begin(); j != listEnd; ++j)
    {
      result += *j;
    }
    output << result << ' ';
  }
  output << '\n';
}

