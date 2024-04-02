#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "token.hpp"

int main()
{
  using namespace erohin;
  std::string string_token;
  std::istringstream input("23 - 98 * ( 9 - 2 )");
  while (input >> string_token)
  {
    std::cout << string_token << " ";
  }
  Operand(0ull);
}
