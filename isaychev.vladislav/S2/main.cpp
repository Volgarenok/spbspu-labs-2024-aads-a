#include <iostream>
#include <fstream>
#include "dataArray.hpp"
#include "inputInfix.hpp"
#include "convertInfToPostf.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  Queue< std::string > infExp;
  Queue< std::string > postfExp;
  if (argc == 1)
  {
    while (!std::cin.eof())
    {
      inputInfix(std::cin, infExp);
    }
    std::cout << "done input\n";
//    convertInfToPostf(infExp, postfExp);
    while (!infExp.empty())
    {
      std::cout << infExp.front();
      infExp.pop();
    }
    std::cout << '\n';
  }
  else if (argc == 2)
  {
    std::fstream input(argv[1]);
  }
}
