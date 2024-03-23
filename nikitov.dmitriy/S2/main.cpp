#include <iostream>
#include <fstream>
#include <list.hpp>
#include "queue.hpp"
#include "expression_type.hpp"
#include "input_list.hpp"
#include "solve_expression.hpp"
#include "convert_expression.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  List< Queue< ExpressionType > > expressionList;

  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      inputList(expressionList, input);
    }
    else
    {
      inputList(expressionList, std::cin);
    }

    List< Queue< ExpressionType > > newExpressionList;
    for (auto i = expressionList.begin(); i != expressionList.end(); ++i)
    {
      newExpressionList.push_back(convertExpression(*i));
    }

    for (auto i = newExpressionList.begin(); i != newExpressionList.end(); ++i)
    {
      if (i != newExpressionList.begin())
      {
        std::cout << ' ';
      }
      std::cout << solveExpression(*i);
    }
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
