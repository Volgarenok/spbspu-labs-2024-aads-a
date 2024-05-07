#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
#include "calculatePostfix.hpp"
#include "getExpression.hpp"
#include "postfixFromInfix.hpp"

int main()
{
  using namespace grechishnikov;

  Queue< std::string > b;
  Queue< std::string > temp;
  Queue< std::string > cl;
  std::string str;
  Stack< long long > res;
  try
  {
    while (!std::cin.eof())
    {
      getline(std::cin, str);
      if (std::cin.eof())
      {
        continue;
      }
      b = getExpression(str);
      temp = postfixFromInfix(b);
//      auto b2 = temp;
//      while (!b2.empty())
//      {
//        std::cout << b2.top();
//        b2.pop();
//      }
//      std::cout << calculatePostfix(temp);
      res.push(calculatePostfix(temp));
      b = cl;
      temp = cl;
    }
    while (!res.empty())
    {
      std::cout << res.top() << '\n';
      res.pop();
    }
  }
  catch(std::exception &e)
  {
    std::cout << e.what() << '\n';
  }
}
