#include "inputOutput.hpp"
#include <iostream>
#include <string>
#include "list.hpp"

void outputNames(List<std::pair<std::string, List<size_t>>>& list)
{
  for (auto it = list.cbegin(); it != list.cend(); ++it)
  {
    std::cout << it->first;
    auto temp = it;
    ++temp;
    if (temp != list.cend())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

void outputSums(List<size_t> numbers)
{
  for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
  {
    std::cout << *it;
    auto temp = it;
    ++temp;
    if (temp != numbers.cend())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

void input(std::istream& input, List<std::pair<std::string, List<size_t>>>& list)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    list.push_front({ line, List<size_t>{} });
    while (input >> line)
    {
      try
      {
        size_t number = std::stoull(line);
        list.front().second.push_back(number);
      }
      catch (const std::invalid_argument&)
      {
        break;
      }
    }
  }
}
