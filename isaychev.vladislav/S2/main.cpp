#include <iostream>
#include <fstream>
#include "dataArray.hpp"
#include "inputInfix.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  Queue< char > infExp;
  if (argc == 1)
  {
    while (!std::cin.eof())
    {
      inputInfix(std::cin, infExp);
    }
    while (!infExp.empty())
    {
      std::cout << infExp.front();
      infExp.pop();
     }
    std::cout << "\n";
  }
  else if (argc == 2)
  {
    std::fstream input(argv[1]);
  }
}
