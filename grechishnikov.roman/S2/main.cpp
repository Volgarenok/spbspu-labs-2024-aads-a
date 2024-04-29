#include <iostream>
#include "queue.hpp"
#include "calculatePostfix.hpp"
#include "getExpression.hpp"

int main()
{
  using namespace grechishnikov;

  Queue< std::string > b;
  std::string str;
  getline(std::cin, str);
  try
  {
    b = getExpression(str);
    std::cout << calculatePostfix(b) << '\n';
  }
  catch(std::exception &e)
  {
    std::cout << e.what() << '\n';
  }
}
