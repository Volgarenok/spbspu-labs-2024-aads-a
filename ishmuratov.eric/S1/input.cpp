#include "input.hpp"

void ishmuratov::inputList(List< std::pair< std::string, List< size_t > > > & pairs, std::istream & input)
{
  std::string str;
  size_t num = 0;
  while (input)
  {
    input >> str;
    if (str.empty())
    {
      break;
    }
    pairs.pushBack({ str, List< size_t >() });
    while (input >> num)
    {
      pairs.back().second.pushBack(num);
    }
    if (!input.eof())
    {
      input.clear();
    }
  }
}
