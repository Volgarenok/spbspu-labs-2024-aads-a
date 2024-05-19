#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <map>
#include "tree.hpp"
#include "sum_func.hpp"
#include "commands.hpp"

int main()
{
  using namespace namestnikov;
  Tree< int, std::string > myMap;
  while (!std::cin.eof())
  {
    std::cin.clear();
    int keyNumber = 0;
    std::string value = "";
    while (std::cin >> keyNumber >> value)
    {
      myMap.insert(keyNumber, value);
    }
  }
  std::string output = "";
  int result = 0;
  descending(result, output, myMap);
  std::cout << result;
  std::cout << output << "\n";
}
