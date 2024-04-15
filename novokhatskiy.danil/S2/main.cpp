#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "calculate_expression.hpp"
#include "convert_expression.hpp"
#include "input_infix.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "tokens.hpp"

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  Queue< Queue< InfixType > > infixQueue;
  try
  {
    if (argc == 2)
    {
      std::ifstream in(argv[1]);
      inputInfix(infixQueue, in);
    }
    else if (argc == 1)
    {
      inputInfix(infixQueue, std::cin);
    }
    else
    {
      std::cerr << "Wrong input arguments\n";
      return 1;
    }
    while (!infixQueue.empty())
    {
      Queue< InfixType > tmp = infixQueue.drop();
      Queue< Postfix > res = convertExpression(std::move(tmp));
      std::cout << calculatePostExp(std::move(res)) << '\n';
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
