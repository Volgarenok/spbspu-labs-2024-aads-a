#include <iostream>
#include <fstream>
#include "inputInfix.hpp"
#include "convertInfToPostf.hpp"
#include "calculateExpression.hpp"
#include "tokens.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  std::istream * input = nullptr;
  std::ifstream file;
  if (argc == 1)
  {
    input = std::addressof(std::cin);
  }
  else
  {
    file.open(argv[1]);
    input = std::addressof(file);
  }

  Stack< long long int > results;
  try
  {
    while (!(*input).eof())
    {
      Queue< Token > infExp;
      Queue< Token > postfExp;
      try
      {
        inputInfix(*input, infExp);
      }
      catch (const std::length_error &)
      {
        continue;
      }
      convertInfToPostf(infExp, postfExp);
      results.push(calculateExpression(postfExp));
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (!results.empty())
  {
    std::cout << results.top();
    results.pop();
    while (!results.empty())
    {
      std::cout << " " << results.top();
      results.pop();
    }
  }
  std::cout << "\n";
}
