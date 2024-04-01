#include <iostream>
#include <fstream>

#include "stack.hpp"
#include "queue.hpp"
#include "getInfix.hpp"
#include "infixToPostfix.hpp"

int main(int argc, char *argv[])
{
  using namespace zhalilov;
  Stack< Queue< InfixToken > > infixes;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    getInfixesFromStream(infixes, file);
  }
  else
  {
    getInfixesFromStream(infixes, std::cin);
  }
  Stack< Queue< PostfixToken > > postfixes;
  try
  {
    while (!infixes.empty())
    {
      Queue< PostfixToken > expression;
      infixToPostfix(infixes.top(), expression);
      postfixes.push(expression);
      infixes.pop();
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }
}
