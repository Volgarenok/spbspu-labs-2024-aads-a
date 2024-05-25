#include <fstream>
#include "evaluatePostfix.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;

  Queue< long long int > resultQueue;
  std::string line;
  char symb = {};

  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    while (infile.get(symb))
    {
      if (symb == '\n')
      {
        if (!line.empty())
        {
          try
          {
            std::string postfixExp = infixToPostfix(line);
            evaluatePostfixExpression(postfixExp, resultQueue);
          }
          catch (const std::exception& e)
          {
            std::cerr << "Error: " << e.what() << '\n';
            return 1;
          }
          line.clear();
        }
      }
      else
      {
        line += symb;
      }
    }
    if (!line.empty())
    {
      try
      {
        std::string postfixExp = infixToPostfix(line);
        evaluatePostfixExpression(postfixExp, resultQueue);
      }
      catch (const std::exception& e)
      {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
      }
    }
  }
  else
  {
    while (std::cin.get(symb))
    {
      if (symb == '\n')
      {
        if (!line.empty())
        {
          try
          {
            std::string postfixExp = infixToPostfix(line);
            evaluatePostfixExpression(postfixExp, resultQueue);
          }
          catch (const std::exception& e)
          {
            std::cerr << "Error: " << e.what() << '\n';
            return 1;
          }
          line.clear();
        }
      }
      else
      {
        line += symb;
      }
    }
    if (!line.empty())
    {
      try
      {
        std::string postfixExp = infixToPostfix(line);
        evaluatePostfixExpression(postfixExp, resultQueue);
      }
      catch (const std::exception& e)
      {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
      }
    }
  }
  printReverse(resultQueue);
  std::cout << '\n';
  return 0;
}
