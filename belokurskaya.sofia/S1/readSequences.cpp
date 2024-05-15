#include "readSequences.hpp"

void belokurskaya::readSequences(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences)
{
  std::string name = "";

  while (in >> name)
  {
    List< size_t > sequence;
    size_t number = 0;
    while (in >> number)
    {
      sequence.push_back(number);
    }
    if (!in.eof())
    {
      in.clear();
    }
    sequences.push_back({name, sequence});
  }
}
