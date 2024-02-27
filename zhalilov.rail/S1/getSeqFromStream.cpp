#include "getSeqFromStream.hpp"

#include <istream>

void zhalilov::getSeqFromStream(List< pair > &sequences, std::istream &input)
{
  std::string seqName = "";
  size_t currNum = 0;
  while (!input.eof())
  {
    List< size_t > numbers;
    input >> seqName;
    while (input >> currNum)
    {
      numbers.push_back(currNum);
    }
    auto pair = std::make_pair(seqName, numbers);
    sequences.push_back(pair);
  }
  input.clear();
}
