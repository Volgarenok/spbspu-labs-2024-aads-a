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

  char nextOperator = std::cin.peek();
  if (!(std::isdigit(nextOperator)))
  {
    rebdev::pushOperation(operationStack, postfixQueue, nextOperator);
  }

  while (!std::cin.eof())
  {
    long long inputNum = 0;
    std::cin >> inputNum;
    postfixQueue.push(rebdev::node(inputNum));

    if ((!std::cin) && (!std::cin.eof()))
    {
      std::cerr << "input error!\n";
      return 1;
    }
    else if (std::cin.eof())
    {
      break;
    }

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

  while (operationStack.size() > 0)
  {
    postfixQueue.push(operationStack.top());
    operationStack.pop();
  }

  try
  {
    std::cout << rebdev::convertPostfixToNum(postfixQueue);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
