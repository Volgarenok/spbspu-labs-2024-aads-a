#include <iostream>
#include <fstream>
#include "dataArray.hpp"
#include "inputInfix.hpp"
#include "convertInfToPostf.hpp"
#include "calculateExpression.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  Queue< std::string > infExp;
  Queue< std::string > postfExp;
  if (argc == 1)
  {
    while (!std::cin.eof())
    {
      try
      {
        inputInfix(std::cin, infExp);
      }
      catch (const std::invalid_argument & e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
    }
  try
  {
    convertInfToPostf(infExp, postfExp);
  }
  catch(const std::out_of_range & e)
  {
    std::cout << e.what() << "\n";
    return 2;
  }
/*    while (!postfExp.empty())
    {
      std::cout << postfExp.front() << " ";
      postfExp.pop();
    }
    std::cout << '\n';*/
    std::cout << calculateExpression(postfExp) << "\n";
  }
  else if (argc == 2)
  {
    std::fstream input(argv[1]);
  }
}
