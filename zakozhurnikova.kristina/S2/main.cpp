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
    using ull = unsigned long long;
    Queue< std::string > queue;
    Stack < ull > result;
    while(std::cin)
    {
      if (argc == 2)
      {
        std::ifstream input(argv[1]);
        getPostfixFromInfix(input, queue);
        evaluatePostfix(result, queue);
      }
      else
      {
        getPostfixFromInfix(std::cin, queue);
        evaluatePostfix(result, queue);
      }
    }
    outputResult(result);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
