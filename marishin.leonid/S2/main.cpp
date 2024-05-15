#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "getPostfixForm.hpp"
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
      getPostfixForm(in, queue);
      checksPostfix(result, queue);
    }
    else
    {
      getPostfixForm(std::cin, queue);
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
