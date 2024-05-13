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
      std::string num_str;
      while (iss >> num_str) {
        try {
          unsigned long long num = std::stoull(num_str);
          if (num > static_cast<unsigned long long>(std::numeric_limits<int>::max())) {
            throw std::overflow_error("Number out of range");
          }
          numbers.push_front(static_cast<int>(num));
        } catch (const std::invalid_argument&) {
          throw std::overflow_error("Invalid number format");
        } catch (const std::out_of_range&) {
          throw std::overflow_error("Number out of range");
        }
      }
      numbers.reverse();
      sequences.push_front(std::make_pair(name, numbers));
    }
    sequences.reverse();
  }
}
