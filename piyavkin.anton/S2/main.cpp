#include <iostream>
#include <fstream>
#include "input.hpp"
#include "convertpostfix.hpp"
#include "calculate.hpp"

int main(int argc, char* argv[])
{
  using namespace piyavkin;
  List< Queue< InputType > > queues;
  try
  {
    if (argc == 1)
    {
      input(std::cin, queues);
    }
    else if (argc == 2)
    {
      std::ifstream in(argv[1]);
      input(in, queues);
    }
    else
    {
      std::cerr << "The file is not specified correctly\n";
      return 1;
    }
    postfix_t postfix;
    convertPostfix(queues, postfix);
    List< long long > result;
    calculate(postfix, result);
    if (!result.empty())
    {
      for (auto it = result.cbegin(); it != result.cend(); ++it)
      {
        if (it != result.cbegin())
        {
          std::cout << ' ';
        }
        std::cout << *it;
      }
    }
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
