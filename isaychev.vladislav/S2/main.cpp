#include <iostream>
#include <fstream>
#include "dataArray.hpp"
#include "inputInfix.hpp"
#include "convertInfToPostf.hpp"
#include "calculateExpression.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  std::istream * input = nullptr;
  std::ifstream file;
  if (argc == 1)
  {
    input = std::addressof(std::cin);
  }
  else if (argc == 2)
  {
    file.open(argv[1]);
    input = std::addressof(file);
  }
  Stack< long long int > results;
  try
  {
    while (!std::cin.eof())
    {
      Queue< std::string > infExp;
      Queue< std::string > postfExp;
      try
      {
        inputInfix(*input, infExp);
      }
      catch (const std::length_error &)
      {
        continue;
      }
      convertInfToPostf(infExp, postfExp);
/*      while (!postfExp.empty())
      {
        std::cout << postfExp.front() << "\n";
        postfExp.pop();
      }*/
      results.push(calculateExpression(postfExp));
    }
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  while (!results.empty())
  {
    std::cout << results.top() << "\n";
    results.pop();
  }
}
