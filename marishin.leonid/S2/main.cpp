#include <iostream>
#include <fstream>

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
      getPostfixFromInfix(input, queue);
      evaluatePostfix(result, queue);
    }
    else
    {
      getPostfixFromInfix(std::cin, queue);
      evaluatePostfix(result, queue);
    }
    outputResult(std::cout, result);
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
