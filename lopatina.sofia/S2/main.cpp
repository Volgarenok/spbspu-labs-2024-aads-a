#include <iostream>
#include <fstream>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"
#include "types.hpp"
#include "input_expression.hpp"
#include "convert_to_postfix.hpp"
#include "calculate_postfix.hpp"

int main(int argc, char ** argv)
{
  using namespace lopatina;

  Stack< long long > stack_result;
  Queue< Queue< InfixType > > queue_input;
  try
  {
    if (argc == 1)
    {
      while (!std::cin.eof())
      {
        Queue< InfixType > queue_infix;
        inputExpression(std::cin, queue_infix);
        queue_input.push(queue_infix);
      }
    }
    else
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "No such file\n";
        return 1;
      }
      while (!input.eof())
      {
        Queue< InfixType > queue_infix;
        inputExpression(input, queue_infix);
        queue_input.push(queue_infix);
      }
    }
    while (!queue_input.empty())
    {
      Queue< InfixType > queue_infix = queue_input.front();
      if (!queue_infix.empty())
      {
        Queue< PostfixType > queue_postfix = convertToPostfix(queue_infix);
        stack_result.push(calculatePostfix(queue_postfix));
      }
      queue_input.pop();
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (!stack_result.empty())
  {
    std::cout << stack_result.top();
    stack_result.pop();
    while (!stack_result.empty())
    {
      std::cout << ' ' << stack_result.top();
      stack_result.pop();
    }
  }
  std::cout << '\n';
  return 0;
}
