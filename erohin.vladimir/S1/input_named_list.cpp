#include "input_named_list.hpp"
#include <iostream>
#include <string>

void erohin::inputNamedList(std::istream & input, List< named_list > & result)
{
  bool is_invalid_argument = false;
  bool is_out_of_range = false;
  while (!input.eof())
  {
    input.clear();
    std::string list_name;
    input >> list_name;
    result.push_front({ list_name, {} });
    named_list & current_line = result.front();
    std::string string_number;
    int elem = 0;
    while (input.peek() != '\n' && !input.eof())
    {
      input >> string_number;
      try
      {
        elem = stoi(string_number);
        current_line.number_list.push_front(elem);
      }
      catch (const std::invalid_argument &)
      {
        is_invalid_argument = true;
      }
      catch (const std::out_of_range &)
      {
        is_out_of_range = true;
      }
    }
    if (input.eof() && list_name == "")
    {
      result.pop_front();
    }
    current_line.number_list.reverse();
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
