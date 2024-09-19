#include <iostream>
#include <fstream>
#include "calculate_expression.hpp"
#include "convert_expression.hpp"
#include "expression_types.hpp"
#include "input_expressions.hpp"
#include "symbols.hpp"
#include "stack.hpp"
#include "queue.hpp"

int main(int argc, char * argv[])
{
  using namespace lebedev;
  Queue< Queue< InfixExpression > > queue_infix;
  try
  {
    if (argc == 2)
    {
      std::ifstream finput(argv[1]);
      inputInfixExpression(queue_infix, finput);
    }
    else if (argc == 1)
    {
      inputInfixExpression(queue_infix, std::cin);
    }
    else
    {
      std::cerr << "ERROR: Wrong command line arguments" << '\n';
      return 1;
    }

    Stack< long long > stack_res;
    while (!queue_infix.empty())
    {
      Queue< InfixExpression > curr_infix_expr = queue_infix.front();
      queue_infix.pop();
      Queue< PostfixExpression > curr_postfix_expr = convertExpression(curr_infix_expr);
      stack_res.push(calculatePostfixExpr(curr_postfix_expr));
    }
    if (!stack_res.empty())
    {
      std::cout << stack_res.top();
      stack_res.pop();
    }
    while (!stack_res.empty())
    {
      std::cout << " ";
      std::cout << stack_res.top();
      stack_res.pop();
    }
    std::cout << "\n";
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
