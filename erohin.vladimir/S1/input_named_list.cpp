#include "input_named_list.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <limits>

void erohin::inputNamedList(std::istream & input, List< named_list > & result)
{
  constexpr int_type max_value = std::numeric_limits< int_type >::max();
  bool is_invalid_argument = false;
  bool is_out_of_range = false;
  while (!input.eof())
  {
    input.clear();
    std::string name;
    input >> name;
    std::string string_number;
    List< int_type > num_list;
    while (input.peek() != '\n' && input >> string_number)
    {
      int_type elem = 0;
      try
      {
        elem = stoi(string_number);
      }
      catch (const std::invalid_argument &)
      {
        is_invalid_argument = true;
      }
      catch (const std::out_of_range &)
      {
        elem = max_value;
        is_out_of_range = true;
      }
      num_list.push_front(elem);
    }
    if (name != "")
    {
      num_list.reverse();
      result.push_front(std::make_pair(name, std::move(num_list)));
    }
  }
  result.reverse();
  if (is_invalid_argument)
  {
    throw std::invalid_argument("Not a number was inputed");
  }
  if (is_out_of_range)
  {
    throw std::out_of_range("Too big number was inputed");
  }
}
