#include "inputList.hpp"

void baranov::inputList(std::istream & input, ds_t & list)
{
  size_t number = 0;
  std::string name = "";
  while (!input.eof())
  {
    input.clear();
    input >> name;
    List< size_t > in_lst;
    while (input >> number)
    {
      in_lst.push_back(number);
    }
    list.push_back(std::make_pair(name, in_lst));
  }
}
