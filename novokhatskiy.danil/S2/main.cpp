#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <stack.hpp>
#include <queue.hpp>
#include "calculate_expression.hpp"
#include "convert_expression.hpp"
#include "input_infix.hpp"
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
    Stack< long long > stack;
    while (!infixQueue.empty())
    {
      Queue< InfixType > tmp = infixQueue.front();
      infixQueue.pop();
      Queue< Postfix > res = convertExpression(std::move(tmp));
      stack.push(calculatePostExp(std::move(res)));
    }
    bool firstExpression = true;
    while (!stack.empty())
    {
      if (!firstExpression)
      {
        std::cout << ' ';
      }
      firstExpression = false;
      std::cout << stack.top();
      stack.pop();
    }
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
