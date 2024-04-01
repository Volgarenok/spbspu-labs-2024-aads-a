#include <iostream>
#include <fstream>

#include "stack.hpp"
#include "queue.hpp"
#include "getInfix.hpp"
#include "infixToPostfix.hpp"
#include "calculateExpr.hpp"

int main(int argc, char *argv[])
{
  using namespace zhalilov;
  Stack< Queue< InfixToken > > infixes;
  Queue< long long > results;
  try
  {
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
    while (!infixes.empty())
    {
      Queue< PostfixToken > expression;
      infixToPostfix(infixes.top(), expression);
      postfixes.push(expression);
      infixes.pop();
    }
    while (!postfixes.empty())
    {
      results.push(calculateExpr(postfixes.top()));
      postfixes.pop();
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }
  while (!results.empty())
  {
    std::cout << results.front() << '\n';
    results.pop();
  }
}
