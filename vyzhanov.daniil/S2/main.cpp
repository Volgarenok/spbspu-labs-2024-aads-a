#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "inputInfix.hpp"
#include "infixToPostfix.hpp"
#include "calculatePostfix.hpp"
#include "outputRes.hpp"
#include "types.hpp"

int main(int argc, char* argv[])
{
  using namespace vyzhanov;
  Queue< Queue< Token > > expressions;
  Stack< long long > results;
  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (input.is_open())
      {
        inputInfix(expressions, input);
        infixToPostfix(expressions);
        calculatePostfix(expressions, results);
      }
      else
      {
        std::cerr << "Cannot open file\n";
        return 1;
      }
    }
    else
    {
      inputInfix(expressions, std::cin);
      infixToPostfix(expressions);
      calculatePostfix(expressions, results);
    }
    outputResult(std::cout, results);
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
