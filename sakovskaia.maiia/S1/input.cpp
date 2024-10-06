#include "input.hpp"

void sakovskaia::input(std::istream & input, List< std::pair< std::string, ullList > > & list)
{
  std::string arg = "";
  input >> arg;
  while (input)
  {
    ullList numbers;
    std::string token = "";
    while (input >> token && token.find_first_not_of("01234567890"))
    {
      try
      {
        numbers.push_back(std::stoull(token));
      }
      catch (const std::invalid_argument &)
      {
        break;
      }
    }
    list.push_back({arg, std::move(numbers)});
    arg = token;
  }
}
