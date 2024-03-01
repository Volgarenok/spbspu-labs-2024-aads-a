#include <iostream>
#include <utility>
#include <string>
#include <stdexcept>
#include "list.hpp"

int main()
{
  using namespace erohin;
  using named_list = std::pair< std::string, List< int > >;
  List< named_list > sequence;
  while (!std::cin.eof())
  {
    sequence.push_front({ "", {} });
    named_list & current_line = sequence.front();
    std::cin.clear();
    std::cin >> current_line.first;
    int elem = 0;
    while (std::cin >> elem)
    {
      try
      {
        current_line.second.push_front(elem);
      }
      catch (const std::bad_alloc &)
      {
        std::cout << "Cannot allocate memory\n";
        return 1;
      }
    }
  }
  return 0;
}
