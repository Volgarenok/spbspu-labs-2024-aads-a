#include <iostream>
#include <utility>
#include <string>
#include <cctype>
#include <stdexcept>
#include "list.hpp"

int main()
{
  using namespace erohin;
  using named_list = std::pair< std::string, List< int > >;
  List< named_list > lines;
  while (!std::cin.eof())
  {
    lines.push_front({ "", {} });
    named_list & current_line = lines.front();
    std::cin.clear();
    std::cin >> current_line.first;
    std::string string_number;
    int elem = 0;
    while (std::cin.peek() != '\n' && !std::cin.eof())
    {
      std::cin >> string_number;
      try
      {
        elem = stoi(string_number);
        current_line.second.push_front(elem);
      }
      catch (const std::invalid_argument &)
      {
        std::cerr << "Input is not a number\n";
      }
      catch (const std::out_of_range &)
      {
        std::cerr << "Number is too big\n";
      }
      catch (const std::bad_alloc &)
      {
        std::cout << "Cannot allocate memory\n";
        return 1;
      }
    }
    current_line.second.reverse();
  }
  lines.reverse();
  for (auto line : lines)
  {
    std::cout << line.first;
    for (auto elem : line.second)
    {
      std::cout << " " << elem;
    }
    std::cout << "\n";
  }
  return 0;
}
