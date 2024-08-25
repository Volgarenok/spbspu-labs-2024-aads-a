#include "infixToPostfix.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  using namespace chernov;
  Queue< Queue< std::string > > infix_queue;
  try
  {
    if (argc == 1)
    {
      inputInfix(std::cin, infix_queue);
    }
    else if (argc == 2)
    {
      std::ifstream in;
      in.open(argv[1]);
      inputInfix(in, infix_queue);
      in.close();
    }
    else
    {
      std::cerr << "Incorrect input arguments\n";
      return 1;
    }
  }
}
