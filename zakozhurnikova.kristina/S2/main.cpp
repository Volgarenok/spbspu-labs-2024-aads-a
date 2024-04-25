#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "getPostfixFromInfix.hpp"
#include "evaluatePostfix.hpp"
#include "outputResult.hpp"


int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  try
  {
    Queue< std::string > queue;
    Stack< long long > result;
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (input.is_open())
      {
        getPostfixFromInfix(input, queue);
        evaluatePostfix(result, queue);
      }
      else
      {
        std::cerr << "Cannot open file\n";
        return 1;
      }
    }
    else
    {
      getPostfixFromInfix(std::cin, queue);
      evaluatePostfix(result, queue);
    }
    outputResult(std::cout, result);
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
