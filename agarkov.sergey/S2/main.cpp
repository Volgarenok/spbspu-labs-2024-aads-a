#include <iostream>
#include <string>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
 
int main()
{
  std::string line;
  std::getline(std::cin, line);
  agarkov::Queue< std::string > infix = agarkov::convertStringToInfix(line);
  convertInfixToPostfix(infix);
}
