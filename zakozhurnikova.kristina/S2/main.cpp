#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
    }
    else
    {
    }

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
