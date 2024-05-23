#include "input.hpp"
#include "cctype"

input_it_t marishin::input(input_it_t first, input_it_t second, std::string& dest)
{
  while(!std::isspace(*first))
  {
    if (first == second)
    {
      return first;
    }
    dest.push_back(*first++);
  }
  return ++first;
}
