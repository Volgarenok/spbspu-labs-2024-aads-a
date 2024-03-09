#include "outputFunctions.hpp"

void baranov::printNames(std::ostream & output, ds_t & list)
{
  auto end = list.end();
  for (auto i = list.begin(); i != end; ++i)
  {
    std::cout << "o";
    output << i->first;
    if (i + 1 == end)
    {
      output << '\n';
    }
    else
    {
      output << ' ';
    }
  }
}

void baranov::printLists(std::ostream & output, listOfLists & lists)
{
  auto listsEnd = lists.end();
  for (auto i = lists.begin(); i != listsEnd; ++i)
  {
    auto listEnd = (*i).end();
    for (auto j = (*i).begin(); j != listEnd; ++i)
    {
      output << *j;
    }
  }
}

