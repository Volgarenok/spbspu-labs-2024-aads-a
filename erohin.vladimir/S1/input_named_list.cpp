#include "input_named_list.hpp"
#include <iostream>
#include <string>
#include <utility>

void erohin::inputNamedList(std::istream & input, named_list & result)
{
  input >> result.first;
  uint64_t number;
  while (input >> number)
  {
    result.second.push_front(number);
  }
  result.second.reverse();
}

void erohin::inputNamedListList(std::istream & input, List< named_list > & result)
{
  while (!input.eof())
  {
    input.clear();
    named_list current_line;
    inputNamedList(input, current_line);
    if (current_line.first != "")
    {
      result.push_front(current_line);
    }
  }
  result.reverse();
}
