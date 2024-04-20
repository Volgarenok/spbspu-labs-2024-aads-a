#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include "infixToPostfix.hpp"
#include "utilities.hpp"
#include "calcultPostfix.hpp"
#include "postfixType.hpp"

int main(int argc, char* argv[])
{
  std::queue<PostfixType> numb;
  std::stack<long long> infix;

  if (argc == 2)
  {
    std::ifstream inputFile(argv[1]);
    infixToPostFix(inputFile, numb);
  }
  else
  {
    infixToPostFix(std::cin, numb);
  }

  long long rez = 0;
  rez = calcult(numb);

  std::cout << rez;
  return 0;
}

