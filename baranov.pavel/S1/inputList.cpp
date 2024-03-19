#include "inputList.hpp"

void baranov::inputList(std::istream & input, ds_t & list)
{
  std::string str = "";
  input >> str;
  while (input)
  {
    std::string name = "";
    input >> name;
    if (name == "")
    {
      throw std::logic_error("No list name");
    }
    List< size_t > numList;
    size_t number;
    while (input >> number)
    {
      numList.push_back(number);
    }
    list.push_back(std::make_pair(name, numList));
    if (!input.eof())
    {
      input.clear();
    }
  }
}

