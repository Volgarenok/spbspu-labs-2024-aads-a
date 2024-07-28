#include <iostream>
#include <fstream>
#include <stdexcept>
#include "stack.hpp"
#include "calculatePostfix.hpp"

int main(int argc, char* argv[])
{
  using namespace grechishnikov;
  Stack< long long > res;
  try
  {
    if (argc == 1)
    {
      res = calculateExpressions(std::cin);
    }
    else if (argc == 2)
    {
      std::ifstream input(argv[1]);
      res = calculateExpressions(input);
    }
    else
    {
      throw std::logic_error("Invalid optiom was passed");
    }
  }
  catch(std::exception &e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }
  if (!res.empty())
  {
    std::cout << res.top();
    res.pop();
  }
  while (!res.empty())
  {
    std::cout << " " << res.top();
    res.pop();
  }
  std::cout << '\n';
}
