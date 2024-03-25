#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_type.hpp"
#include "input_list.hpp"
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
      inputList(infixQueue, input);
    }
    else
    {
      inputList(infixQueue, std::cin);
    }

    Stack< Queue< PostfixType > > postfixStack;
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
