#include <iostream>
#include <fstream>
#include <stdexcept>
#include "token.hpp"
#include "infix_expression.hpp"
#include "postfix_expression.hpp"

#include <queue>
#include <stack>

int main(int argc, char ** argv)
{
  using namespace erohin;
  std::queue< PostfixExpression > expr_lines;
  std::stack< long long > results;
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
    calculatePostfixExpressions(results, expr_lines);
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
