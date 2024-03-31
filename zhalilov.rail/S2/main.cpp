#include <iostream>
#include <fstream>

#include "stack.hpp"
#include "queue.hpp"
#include "getInfix.hpp"

int main(int argc, char *argv[])
{
  using namespace zhalilov;
  Stack< Queue< InfixToken > > infixes;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    getInfixesFromStream(infixes, file);
  }
  else
  {
    getInfixesFromStream(infixes, std::cin);
  }
}
