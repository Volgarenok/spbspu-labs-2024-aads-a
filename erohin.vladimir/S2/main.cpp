#include <iostream>
#include <fstream>
#include <stdexcept>
#include "token.hpp"
#include "postfix_expression.hpp"
#include "queue.hpp"
#include "stack.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  Queue< PostfixExpression > expr_lines;
  Stack< long long > results;
  bool isAnyExpressionCorrect = true;
  try
  {
    if (argc == 1)
    {
      inputPostfixExpressionLines(std::cin, expr_lines);
    }
    else if (argc == 2)
    {
      std::ifstream file(argv[1]);
      inputPostfixExpressionLines(file, expr_lines);
    }
    else
    {
      std::cerr << "Wrong number of CLA\n";
      return 1;
    }
    while (!expr_lines.empty())
    {
      results.push(expr_lines.front().evaluate()());
      expr_lines.pop();
    }
  }
  catch (...)
  {
    isAnyExpressionCorrect = false;
  }
  if (isAnyExpressionCorrect)
  {
    if (!results.empty())
    {
      std::cout << results.top();
      results.pop();
    }
    else
    {
      return 0;
    }
    while (!results.empty())
    {
      std::cout << " " << results.top();
      results.pop();
    }
    std::cout << "\n";
    return 0;
  }
  else
  {
    std::cerr << "Some errors in expressions were found\n";
    return 2;
  }
}
