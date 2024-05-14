#include "readinput.hpp"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include "list.hpp"

namespace petuhov
{
  void readInput(List< std::pair< std::string, List< size_t > > >& sequences, std::istream& input)
  {
    std::string line;
    while (std::getline(input, line))
    {
      std::istringstream iss(line);
      std::string name;
      if (!(iss >> name))
      {
        continue;
      }
      List< size_t > numbers;
      std::string num_str;
      while (iss >> num_str)
      {
        size_t num = std::stoull(num_str);
        numbers.push_front(num);
      }
      numbers.reverse();
      sequences.push_front(std::make_pair(name, numbers));
    }
    sequences.reverse();
  }
}
