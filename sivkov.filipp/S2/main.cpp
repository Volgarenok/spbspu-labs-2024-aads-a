#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include "infixToPostfix.hpp"
#include "utilities.hpp"
#include "calcultPostfix.hpp"

int main(int argc, char* argv[])
{
  std::queue<char> numb;
  std::stack<int> infix;

  if (argc == 2)
  {
    std::ifstream inputFile(argv[1]);
    infixToPostFix(inputFile, numb);
  }
  else
  {
    infixToPostFix(std::cin, numb);
  }

  int rez = 0;
  rez = calcult(numb);

  std::cout << rez;
  return 0;
}
