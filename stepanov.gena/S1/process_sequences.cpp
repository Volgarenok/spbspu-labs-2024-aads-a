#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>

#include "process_sequences.hpp"
#include "node.hpp"
#include "list.hpp"

namespace stepanov
{
  void process_sequences()
  {
    std::vector<std::pair<std::string, List<int>>> sequences;
    std::string line;

    while (std::getline(std::cin, line))
    {
      std::istringstream iss(line);
      std::string name;
      iss >> name;
      List<int> numbers;
      int num;
      while (iss >> num)
      {
        numbers.push_back(num);
      }
      sequences.push_back({ name, std::move(numbers) });
    }
  }
}


