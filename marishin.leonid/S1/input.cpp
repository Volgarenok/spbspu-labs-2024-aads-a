#include "input.hpp"

void marishin::inputList(LinkedList< std::pair< std::string, LinkedList< size_t > > > & pairs, std::istream & input)
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
    pairs.push_back({ str, LinkedList< size_t >() });
    while (input >> num)
    {
      pairs.back().second.push_back(num);
    }
    if (!input.eof())
    {
      input.clear();
    }
  }
}
