#include <iostream>
#include <fstream>
#include <stdexcept>
#include "token.hpp"
#include "infix_expression.hpp"
#include "postfix_expression.hpp"

#include <queue>
#include <stack>
#include "stack.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;

  Stack< int > stack(std::list< int >({ 0, 1, 2, 3 }));
  for (int i = 4; i < 10; ++i)
  {
    stack.push(i);
  }
  while (!stack.empty())
  {
    std::cout << stack.top();
    stack.pop();
  }


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
