#include "readinput.hpp"
#include <iostream>
#include <sstream>
#include "list.hpp"

namespace petuhov
{
  void readInput(List< std::pair< std::string, List< int > > > &sequences, std::istream &input)
  {
    std::string line;

    while (std::getline(input, line))
    {
      size_t pos = line.find(' ');
      std::string name = line.substr(0, pos);
      List< int > nums;

      if (pos != std::string::npos)
      {
        std::string num_string = line.substr(pos + 1);
        std::istringstream num_stream(num_string);
        int num;
        while (num_stream >> num)
        {
          nums.push_front(num);
        }
      }
      sequences.push_front(std::make_pair(name, nums));
    }
  }
}
