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
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  Queue< Queue< std::string > > postfix_queue;
  Stack< long long int > result_stack;
  try
  {
    convertToPostfix(infix_queue, postfix_queue);
    convertToValues(postfix_queue, result_stack);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
