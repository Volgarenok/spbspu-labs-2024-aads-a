#include <iostream>
#include <fstream>

#include "solvedata.hpp"

int main(int argc, char* argv[])
{
  using namespace gladyshev;
  Stack< long long int > results;
  try
  {
     if (argc == 2)
    {
      std::ifstream file(argv[1]);
      inputExpression(file, results);
    }
    else
    {
      inputExpression(std::cin, results);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  if (!results.empty())
  {
    std::cout << results.top();
    results.pop();
  }
  while (!results.empty())
  {
    std::cout << " " << results.top();
    results.pop();
  }
  std::cout << "\n";
}
