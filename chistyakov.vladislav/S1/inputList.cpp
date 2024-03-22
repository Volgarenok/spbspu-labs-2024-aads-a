#include "inputList.hpp"
#include <iostream>
#include "list.hpp"

void chistyakov::inputList(std::istream & input, List< std::pair< std::string, List < int > > > & list)
{
  std::string name = "";
  while (std::getline(input, name, ' '))
  {
    if (!input)
    {
      throw std::invalid_argument("Bad input!");
    }

    std::size_t c = name.find('\n');
    if (c != std::string::npos)
    {
      name.replace(c, 1, " ");
    }

    List< int > nums;
    inputNums(input, nums);
    list.push_back({name, nums});
  }
}

void chistyakov::inputNums(std::istream & input, List< int > & nums)
{
  int num = 0;

  while (input >> num)
  {
    nums.push_back(num);
  }
  input.clear();
}
