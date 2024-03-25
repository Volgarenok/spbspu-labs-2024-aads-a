#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "expression_type.hpp"
#include "input_list.hpp"
#include "solve_expression.hpp"
#include "convert_expression.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  Queue< Queue< InfixType > > expressionQueue;

  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      inputList(expressionQueue, input);
    }
    else
    {
      inputList(expressionQueue, std::cin);
    }

    Queue< Queue< PostfixType > > newExpressionQueue;
    while (!expressionQueue.empty())
    {
      newExpressionQueue.push(convertExpression(expressionQueue.drop()));
    }

    bool notFirst = false;
    while (!newExpressionQueue.empty())
    {
      if (notFirst)
      {
        std::cout << ' ';
      }
      notFirst = true;
      std::cout << solveExpression(newExpressionQueue.drop());
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
