#include <iostream>
#include <fstream>
#include <string>
#include <stack.hpp>
#include <queue.hpp>
#include "tokens.hpp"
#include "inputPostfix.hpp"
#include "calculatePostfix.hpp"
#include "outputFunction.hpp"

int main(int argc, char * argv [])
{
  using namespace baranov;
  Queue< Queue< Token > > postfixes;
  Stack< long long int > results;
  try
  {
    if (argc == 2)
    {
      std::ifstream file(argv[1]);
      if (!file.is_open())
      {
        throw std::logic_error("Cannot open input file\n");
      }
      inputPostfixes(file, postfixes);
    }
    else
    {
      inputPostfixes(std::cin, postfixes);
    }
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

