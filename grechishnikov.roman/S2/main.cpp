#include <iostream>
#include "queue.hpp"
#include "tokenType.hpp"

int main()
{
  using namespace grechishnikov;
  std::string a = "55235235}";
  std::cout << isOperand(a) << '\n';
  std::string b = "%";
  std::cout << isOperator(b) << '\n';
}
