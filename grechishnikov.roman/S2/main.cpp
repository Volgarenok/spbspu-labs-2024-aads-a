#include <iostream>
#include "queue.hpp"
#include "calculatePostfix.hpp"
#include "getExpression.hpp"
#include "postfixFromInfix.hpp"

int main()
{
  using namespace grechishnikov;

  Queue< std::string > b;
  Queue< std::string > b2;
  Queue< std::string > res;
  std::string str;
  getline(std::cin, str);
  try
  {
    b = getExpression(str);
    res = postfixFromInfix(b);
    b2 = res;
    while (!b2.empty())
    {
      std::cout << b2.top() << '\n';
      b2.pop();
    }
    std::cout << calculatePostfix(res) << '\n';
  }
  catch(std::exception &e)
  {
    std::cout << e.what() << '\n';
  }
}
