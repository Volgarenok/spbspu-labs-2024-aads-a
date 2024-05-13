#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "input.hpp"
#include "checksPostfix.hpp"
#include "output.hpp"

int main(int argc, char* argv[])
{
  using namespace marishin;
  try
  {
    Stack< long long > result;
    Queue< std::string > queue;
    if (argc == 2)
    {
      std::ifstream in(argv[1]);
      input(in, queue);
      checksPostfix(result, queue);
    }
    else
    {
      input(std::cin, queue);
      checksPostfix(result, queue);
    }
    output(std::cout, result);
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
