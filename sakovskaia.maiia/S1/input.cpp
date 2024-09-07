#include "input.hpp"

void sakovskaia::input(std::istream & input, List< std::pair< std::string, ullList > > & list)
{
  std::string arg = "";
  while (input >> arg)
  {
    ullList numbers;
    std::string token = "";
    while (input >> token)
    {
      try
      {
        numbers.push_front(std::stoull(token));
      }
      catch (const std::invalid_argument &)
      {
        break;
      }
    }
    list.push_front({arg, std::move(numbers)});
  }
}
