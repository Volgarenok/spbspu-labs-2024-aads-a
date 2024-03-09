#include "input_named_list.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

void erohin::inputNamedList(std::istream & input, List< named_list > & result)
{
  while (!input.eof())
  {
    input.clear();
    std::string name;
    input >> name;
    std::string string_number;
    List< int_t > num_list;
    int_t elem = 0;
    while (input.peek() != '\n' && input >> string_number)
    {
      elem = std::stoull(string_number);
      num_list.push_front(elem);
    }
    if (name != "")
    {
      num_list.reverse();
      result.push_front(std::make_pair(name, std::move(num_list)));
    }
  }
  result.reverse();
}
