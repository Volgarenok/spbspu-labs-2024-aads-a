#include <iostream>
#include <fstream>
#include <cctype>

#include "myStack.hpp"
#include "myQueue.hpp"
#include "node.hpp"
#include "postfixFunction.hpp"
#include "infixFunction.hpp"

int main(int argc, char ** argv)
{
  std::istream * istreamPointer = &std::cin;
  std::ifstream finput;
  if (argc > 1)
  {
    finput.open(argv[1]);
    istreamPointer = &finput;
    if (finput.peek() == EOF)
    {
      std::cout << '\n';
      return 1;
    }
  }
  std::istream & input = *istreamPointer;

  rebdev::stack< rebdev::node > operationStack;
  rebdev::queue< rebdev::node > postfixQueue;
  while (!input.eof())
  {
    char nextOperator = input.peek();

    if (std::isdigit(nextOperator) && (nextOperator != '-') && (nextOperator != '+'))
    {
      long long num = 0;
      input >> num;
      if (!input)
      {
        std::cerr << "bad number input!\n";
        return 1;
      }
      postfixQueue.push(num);
    }
    else if ((nextOperator == ' ') || (nextOperator == '\n') || (nextOperator == EOF))
    {
      input >> std::noskipws;
      input >> nextOperator;
      input >> std::skipws;
    }
    else
    {
      input >> nextOperator;
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
    return 1;
  }

  return 0;
}
