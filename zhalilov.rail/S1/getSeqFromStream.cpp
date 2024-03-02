#include "getSeqFromStream.hpp"

#include <iostream>

void zhalilov::getSeqFromStream(List< pair > &sequences, std::istream &input)
{
  std::string seqName = "";
  size_t currNum = 0;
  while (input)
  {
    List< size_t > numbers;
    input >> seqName;
    while (input >> currNum)
    {
      numbers.push_back(currNum);
    }
    if (!input.eof())
    {
      input.clear();
    }
    auto pair = std::make_pair(seqName, numbers);
    sequences.push_back(pair);
  }
}
