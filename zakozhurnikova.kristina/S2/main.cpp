#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "getPostfixFromInfix.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  try
  {
    while(std::cin)
    {
      Queue< std::string > queue;
      if (argc == 2)
      {
        std::ifstream input(argv[1]);
        getPostfixFromInfix(input, queue);
//записывать сумму в отдельный список и если всё ок, то вывести, начиная с tail
      }
      else
      {
        getPostfixFromInfix(std::cin, queue);
//        std::cout << res << '\n';
      }
    }
//здесь вывод
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
