#include "inputList.hpp"

void baranov::inputList(std::istream & input, ds_t & sequences)
{
  std::string name = "";
  while (input >> name)
  {
    size_t num = 0;
    List< size_t > nums;
    while (input >> num)
    {
      nums.push_back(num);
      if (input.peek() == '\n')
      {
        break;
      }
    }
    if (!input.eof())
    {
      input.clear();
    }
    sequences.push_back({name, nums});
  }
}

