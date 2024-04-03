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
  try
  {
    std::queue< Token > input_queue;
    if (argc == 1)
    {
      inputInfixExpression(std::cin, input_queue);
    }
    else if (argc == 2)
    {
      std::ifstream file(argv[0]);
      inputInfixExpression(file, input_queue);
    }
    else
    {
      std::cerr << "Wrong number of CLA\n";
      return 1;
    }
    PostfixExpression expr(input_queue);
    if (!input_queue.empty())
    {
      std::cout << expr.evaluate()() << "\n";
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
