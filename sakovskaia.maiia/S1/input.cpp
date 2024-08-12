#include "input.hpp"

void sakovskaia::input(std::istream & input, List< std::pair< std::string, ullList > > & list)
{
  std::string arg = "";
  input >> arg;
  while (!in.eof())
  {
    list.push_front({arg, List< unsigned long long int >()});
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
