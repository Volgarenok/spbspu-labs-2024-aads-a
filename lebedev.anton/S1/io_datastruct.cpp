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

void lebedev::outputPairsNames(std::ostream & output, listOfPairs & pairs)
{
  for (auto pairs_iter = pairs.cbegin(); pairs_iter != pairs.cend(); ++pairs_iter)
  {
    if (pairs_iter != pairs.cbegin())
    {
      output << ' ';
    }
    output << pairs_iter->first;
  }
  output << ' ' << pairs.cend()->first;
}
