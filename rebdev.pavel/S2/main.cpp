#include <iostream>
#include <cctype>

#include "myStack.hpp"
#include "myQueue.hpp"
#include "node.hpp"
#include "postfixFunction.hpp"
#include "infixFunction.hpp"

int main()
{
  rebdev::stack< rebdev::node > operationStack;
  rebdev::queue< rebdev::node > postfixQueue;

  while (!std::cin.eof())
  {
    char nextOperator = std::cin.peek();

    if (std::isdigit(nextOperator) && (nextOperator != '-') && (nextOperator != '+'))
    {
      long long num = 0;
      std::cin >> num;
      postfixQueue.push(num);
    }
    else if ((nextOperator == ' ') || (nextOperator == '\n') || (nextOperator == EOF))
    {
      std::cin >> std::noskipws;
      std::cin >> nextOperator;
      std::cin >> std::skipws;
    }
    else
    {
      std::cin >> nextOperator;
      try
      {
        rebdev::pushOperation(operationStack, postfixQueue, nextOperator);
      }
      catch (const std::exception & e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
  }

  while (operationStack.size() > 0)
  {
    postfixQueue.push(operationStack.top());
    operationStack.pop();
  }

  try
  {
    std::cout << rebdev::convertPostfixToNum(postfixQueue) << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
