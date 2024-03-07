#include "input_named_list.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

void erohin::inputNamedList(std::istream & input, List< named_list > & result)
{
  bool is_invalid_argument = false;
  bool is_out_of_range = false;
  while (!input.eof())
  {
    input.clear();
    std::string name;
    input >> name;
    std::string string_number;
    List< int > number_list;
    int elem = 0;
    while (input.peek() != '\n' && !input.eof())
    {
      input >> string_number;
      try
      {
        elem = stoi(string_number);
        number_list.push_front(elem);
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
    if (name != "")
    {
      number_list.reverse();
      result.push_front({ name, std::move(number_list) });
    }
  }
  if (result.empty())
  {
    throw std::logic_error("List is empty");
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
