#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <map>
#include "tree.hpp"
#include "sum_func.hpp"
#include "commands.hpp"
#include "input_dict.hpp"

int main()
{
  using namespace namestnikov;
  Tree< int, std::string > myMap;
  inputDict(std::cin, myMap);
  std::string output = "";
  int result = 0;
  descending(result, output, myMap);
  std::cout << result;
  std::cout << output << "\n";
}
