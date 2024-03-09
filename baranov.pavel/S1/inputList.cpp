#include "inputList.hpp"

void baranov::inputList(std::istream & input, ds_t & list)
{
  std::string str = "";
  input >> str;
  while (input)
  {
    auto pair = std::make_pair(str, List< size_t >());
    list.push_back(pair);
    while (input >> str && std::isdigit(str[0]))
    {
      list.end()->second.push_back(std::stoull(str));
    }
  }
}

