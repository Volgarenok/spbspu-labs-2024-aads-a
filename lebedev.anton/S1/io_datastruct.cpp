#include "io_datastruct.hpp"

void lebedev::inputDS(std::istream & input, listOfPairs & pairs)
{
  std::string seq_name = "";
  size_t curr_num = 0;
  while (!input.eof())
  {
    input.clear();
    List< size_t > numbers;
    input >> seq_name;
    if (seq_name.empty())
    {
      break;
    }
    while (input >> curr_num)
    {
      numbers.push_back(curr_num);
    }
    auto pair = std::make_pair(seq_name, numbers);
    pairs.push_back(pair);
  }
}
