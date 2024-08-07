#include "outputList.hpp"
#include <iostream>
#include <stdexcept>

void chernov::outNames(const List< namedNumberedList >& list, std::ostream& output)
{
  if (list.isEmpty())
  {
    throw std::logic_error("List is empty");
  }
  auto current = list.cbegin();
  while (current != list.cend())
  {
    output << ' ' << current->first;
    ++current;
  }

}
