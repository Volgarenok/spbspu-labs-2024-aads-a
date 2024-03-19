#include <iostream>
#include <fstream>
#include "stack.hpp"
#include "queue.hpp"
#include "partexpression.hpp"

int main(int argc, char* argv[])
{
  using namespace piyavkin;
  Queue< PartExpression > queue;
  if (argc == 1)
  {
    // input();
  }
  else if (argc == 2)
  {
    std::ifstream in(argv[1]);
    // input();
  }
  else
  {
    std::cerr << "The file is not specified correctly\n";
    return 1;
  }
}
