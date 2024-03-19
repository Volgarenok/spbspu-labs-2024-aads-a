#include <iostream>
#include <fstream>
#include "stack.hpp"
#include "queue.hpp"
#include "input.hpp"
#include "partexpression.hpp"

int main(int argc, char* argv[])
{
  using namespace piyavkin;
  size_t size = 50;
  Queue< char >* queues = new Queue< char >[size]{};
  if (argc == 1)
  {
    input(std::cin, queues, size);
  }
  else if (argc == 2)
  {
    std::ifstream in(argv[1]);
    input(in, queues, size);
  }
  else
  {
    std::cerr << "The file is not specified correctly\n";
    return 1;
  }
  while (!queues[0].empty())
  {
    std::cout << queues[0].drop();
  }
}