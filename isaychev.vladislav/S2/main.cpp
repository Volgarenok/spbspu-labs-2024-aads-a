#include "queue.hpp"
#include "stack.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char * argv[])
{
  if (argc == 1)
  {
    while (!std::cin.eof())
    {
      std::cout << "ya input\n";
    }
  }
  else if (argc = 2)
  {
    std::fstream input(argv[1]);
  }
}
