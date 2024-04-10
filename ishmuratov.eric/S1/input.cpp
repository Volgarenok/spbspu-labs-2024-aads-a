#include "input.hpp"

void ishmuratov::inputList(List< std::pair< std::string, List< size_t > > > & pairs, std::istream & input)
{
  std::string str;
  input >> str;
  while (input)
  {
    pairs.pushBack({ str, List< size_t >() });
    input >> str;
    while (input && std::isdigit(str[0]))
    {
      pairs.back().second.pushBack(std::stoull(str));
      input >> str;
    }
  }
}
