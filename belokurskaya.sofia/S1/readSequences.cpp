#include "readSequences.hpp"

belokurskaya::List< belokurskaya::SequencePair > belokurskaya::readSequences(std::istream& in)
{
  List< SequencePair > sequences;
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
    SequencePair pair(name, sequence);
    sequences.push_back(pair);
  }
  return sequences;
}
