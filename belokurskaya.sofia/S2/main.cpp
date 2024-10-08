#include <fstream>
#include <iostream>
#include <string>

#include "evaluatePostfixExpression.hpp"
#include "infixToPostfix.hpp"
#include <queue.hpp>
#include <stack.hpp>

int main(int argc, char* argv[])
{
  using namespace belokurskaya;
  std::istream* input;
  std::ifstream fileInput;
  Stack< long long int > results;
  if (argc < 2)
  {
    input = &std::cin;
  }
  else
  {
    fileInput.open(argv[1]);
    if (!fileInput.is_open())
    {
      std::cerr << "Unable to open input file\n";
      return 1;
    }
    input = &fileInput;
  }

  std::string line;
  while (std::getline(*input, line))
  {
    if (line.empty())
    {
      continue;
    }
    try
    {
      std::string postfix = infixToPostfix(line);
      long long int result = evaluatePostfixExpression(postfix);
      results.push(result);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  if (!results.empty())
  {
    std::cout << results.top();
    results.pop();
  }

  while (!results.empty())
  {
    std::cout << " " << results.top();
    results.pop();
  }
  std::cout << "\n";
  return 0;
}
