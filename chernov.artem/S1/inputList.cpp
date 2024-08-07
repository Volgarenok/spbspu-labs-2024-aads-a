#include "inputList.hpp"
#include <iostream>
#include <string>

void chernov::inputLists(std::istream& input, List< namedNumberedList >& list)
{
  while (!input.eof())
  {
    input.clear();
    namedNumberedList temp;
    input >> temp.first;

    if (temp.first.empty())
    {
      break;
    }

    size_t num = 0;

    while (input >> num)
    {
      temp.second.push_front(num);
    }

    list.push_back(temp);
  }
}
