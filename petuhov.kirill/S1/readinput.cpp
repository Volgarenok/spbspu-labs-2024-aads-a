#include "readinput.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <sstream>
#include "list.hpp"

namespace petuhov {
  void readInput(List< std::pair< std::string, List< int > > > &sequences, std::istream &input) {
    std::string line;
    while (std::getline(input, line)) {
      std::istringstream iss(line);
      std::string name;
      if (!(iss >> name)) {
        continue;
      }
      List< int > numbers;
      int num;
      while (iss >> num) {
        if (num < 0 || num > std::numeric_limits<int>::max()) {
          throw std::overflow_error("Number out of range");
        }
        numbers.push_front(num);
      }
      numbers.reverse();
      sequences.push_front(std::make_pair(name, numbers));
    }
    sequences.reverse();
  }
}
