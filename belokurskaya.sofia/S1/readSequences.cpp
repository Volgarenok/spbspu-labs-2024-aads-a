#include "readSequences.hpp"

#include <iostream>

belokurskaya::SequenceVector belokurskaya::readSequences(std::istream & in)
{
  SequenceVector sequences;
  std::string name = "";

  while (in >> name)
  {
    List< unsigned long long > sequence;
    size_t number = 0;
    while (in >> number)
    {
      sequence.push_back(number);
    }
    if (!in.eof())
    {
      in.clear();
    }
    sequences.push_back({ name, sequence });
  }
  return sequences;
}
