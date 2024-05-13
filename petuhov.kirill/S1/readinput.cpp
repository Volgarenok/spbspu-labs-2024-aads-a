#include "readinput.hpp"
#include <iostream>
#include "list.hpp"

namespace petuhov
{
  void readInput(List< std::pair< std::string, List< int > > > &sequence, std::istream &input)
  {
    std::string line;

    while (std::getline(input, line))
    {
      size_t pos = line.find(' ');
      std::string name = line.substr(0, pos);
      List< int > nums = {};

      if (pos != std::string::npos)
      {
        std::string num_string = line.substr(pos + 1);
        size_t num_pos = 0;

        while ((pos = num_string.find(' ', num_pos)) != std::string::npos)
        {
          nums.push_front(std::stoi(num_string.substr(num_pos, pos - num_pos)));
          num_pos = pos + 1;
        }
        nums.push_front(std::stoi(num_string.substr(num_pos)));
      }
      sequence.push_front(std::make_pair(name, nums));
    }
  }
}
