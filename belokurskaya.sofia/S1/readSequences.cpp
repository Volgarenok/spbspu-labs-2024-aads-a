#include "readSequences.hpp"

#include <limits>
#include <string>

void belokurskaya::readSequences(std::istream& in, List< std::pair< std::string, List< size_t > > >& sequences)
{
  std::string line;
  List< std::pair< std::string, List< size_t > > > sequenceList;

  while (std::getline(in, line))
  {
    if (line.empty()) continue;

    std::string name;
    List< size_t > numbers;

    size_t index = 0;

    while (index < line.size() && line[index] != ' ')
    {
      name.push_back(line[index]);
      ++index;
    }

    while (index < line.size())
    {
      while (index < line.size() && line[index] == ' ')
      {
        ++index;
      }

      size_t num = 0;
      while (index < line.size() && line[index] >= '0' && line[index] <= '9')
      {
        num = num * 10 + (line[index] - '0');
        ++index;
      }
      numbers.push_back(num);
    }
    sequenceList.push_front({ name, numbers });
  }
  for (const auto& entry : sequenceList)
  {
    sequences.push_front(entry);
  }
}

void belokurskaya::readElem(List< List< size_t > >& out, List< std::pair< std::string, List< size_t > > >& in)
{
  size_t ind = 0;
  auto end = in.end();
  while (true)
  {
    List< size_t > numbers;
    for (auto i = in.begin(); i != end; ++i)
    {
      if (ind < i->second.size())
      {
        auto temp_i = i->second.begin();
        std::advance(temp_i, ind);
        numbers.push_back(*temp_i);
      }
    }
    if (!numbers.empty())
    {
      out.push_back(numbers);
      ++ind;
    }
    else
    {
      break;
    }
  }
}
