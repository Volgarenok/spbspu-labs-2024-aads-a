#include "readinput.hpp"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include "list.hpp"

namespace petuhov
{
  void readInput(List< std::pair< std::string, List< int > > >& sequences, std::istream& input, bool& overflow_occurred)
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
      List< int > numbers;
      std::string num_str;
      while (iss >> num_str)
      {
        try
        {
          unsigned long long num = std::stoull(num_str);
          if (num > static_cast<unsigned long long>(std::numeric_limits<int>::max()))
          {
            overflow_occurred = true;
            continue;
          }
          numbers.push_front(static_cast<int>(num));
        }
        catch (const std::invalid_argument&)
        {
          overflow_occurred = true;
          continue;
        }
        catch (const std::out_of_range&)
        {
          overflow_occurred = true;
          continue;
        }
      }
      numbers.reverse();
      sequences.push_front(std::make_pair(name, numbers));
    }
    sequences.reverse();
  }
}
