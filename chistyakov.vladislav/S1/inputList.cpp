#include "inputList.hpp"
#include <iostream>
#include "list.hpp"

void chistyakov::inputList(std::istream & input, List< std::pair< std::string, List < int > > > & list)
{
  std::string name = "";
  std::string line = "";
  input >> line;

  while (!input.eof())
  {
    name = line;
    List< int > nums;
    inputNums(input, nums);
    list.push_back({name, nums});
  }
}

void chistyakov::inputNums(std::istream & input, List< int > & nums)
{
  std::string digits = "";

  while (input >> digits && std::isdigit(digits[0]))
  {
    std::size_t num = std::stoull(digits);
    nums.push_back(num);
  }

  input.clear();
}
