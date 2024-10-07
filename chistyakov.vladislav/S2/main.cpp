#include <iostream>
#include <string>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "infixToPostfix.hpp"
#include "input.hpp"
#include "calculate.hpp"

int main(int argc, char ** argv)
{
  using namespace chistyakov;

  Stack< Queue< std::string > > results;

  try
  {
    if (argc == 2)
    {
      std::ifstream in(argv[1]);
      inputExp(results, in);
    }
    if (argc == 1)
    {
      inputExp(results, std::cin);
    }
    else
    {
      std::cerr << "Invalid argv\n";
      return 1;
    }

    if (!results.empty())
    {
      Queue< std::string > localResult;
      infixToPostfix(localResult, results.top());
      std::cout << calculate(localResult);
      results.pop();
    }

    while (!results.empty())
    {
      Queue< std::string > localResult;
      infixToPostfix(localResult, results.top());
      std::cout << " " << calculate(localResult);
      results.pop();
    }
    std::cout << "\n";

  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
