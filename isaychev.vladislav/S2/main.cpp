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
  std::string s = "";
  if (argc == 1)
  {
    while (!std::cin.eof())
    {
      try
      {
        std::getline(std::cin, s);
        inputInfix(std::cin, s, infExp);
      }
      catch (const std::invalid_argument & e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
    }
    std::cout << "done input\n";
/*    convertInfToPostf(infExp, postfExp);
    while (!postfExp.empty())
    {
      std::cout << postfExp.front() << " ";
      postfExp.pop();
    }
    std::cout << '\n';
    std::cout << calculateExpression(postfExp) << "\n";
    while (!infExp.empty())
    {
      std::cout << infExp.front() << " ";
      infExp.pop();
    }
    std::cout << '\n';*/
  }
  else if (argc == 2)
  {
    std::fstream input(argv[1]);
  }
}
