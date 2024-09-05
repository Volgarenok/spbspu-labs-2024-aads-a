#include "input.hpp"

void sakovskaia::input(std::istream & input, List< std::pair< std::string, ullList > > & list)
{
  std::string arg = "";
  input >> arg;
  while (input >> arg)
  {
    list.push_front({arg, ullList()});
    while (input >> arg)
    {
      try
      {
        list.front().second.push_front(std::stoull(arg));
      }
      catch (const std::invalid_argument &)
      {
        break;
      }
    }
  }
}
