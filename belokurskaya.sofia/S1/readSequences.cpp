#include "readSequences.hpp"

#include <limits>
#include <string>

void belokurskaya::readSequences(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences)
{
  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty()) continue;

    std::string name;
    size_t index = 0;

    while (index < line.size() && line[index] != ' ')
    {
      name.push_back(line[index]);
      ++index;
    }

    List< size_t > sequence;

    while (index < line.size() && line[index] == ' ')
    {
      ++index;
    }

    while (index < line.size())
    {
      size_t number = 0;
      while (index < line.size() && line[index] >= '0' && line[index] <= '9')
      {
        number = number * 10 + (line[index] - '0');
        ++index;
      }
      sequence.push_back(number);

      while (index < line.size() && line[index] == ' ')
      {
        ++index;
      }
    }

    sequences.push_back({ name, sequence });
  }
}
