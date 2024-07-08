#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
#include "tokens.hpp"
#include "inputPostfix.hpp"
#include "calculatePostfix.hpp"
#include "outputFunction.hpp"

int main()
{
  using namespace baranov;
  Queue< Queue< Token > > postfixes;
  Stack< long long int > results;

  try
  {
    inputPostfixes(std::cin, postfixes);
    calculatePostfixes(postfixes, results);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }

  printResults(std::cout, results);
  std::cout << '\n';
}

