#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_type.hpp"
#include "postfix_expression.hpp"
#include "input_expressions.hpp"
#include "convert_expression.hpp"
#include "solve_expression.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  Queue< Queue< InfixType > > infixQueue;

  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      inputExpressions(infixQueue, input);
    }
    else
    {
      inputExpressions(infixQueue, std::cin);
    }

    Stack< PostfixExpression > postfixStack;
    while (!infixQueue.empty())
    {
      postfixStack.push(convertExpression(infixQueue.drop()));
    }

    bool isFirst = true;
    while (!postfixStack.empty())
    {
      if (!isFirst)
      {
        std::cout << ' ';
      }
      isFirst = false;
      std::cout << solveExpression(postfixStack.drop());
    }
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
