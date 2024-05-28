#include <iostream>
#include <cstring>
#include "secondary_commands.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc == 2 && !strcmp(argv[1], "--help"))
  {
    printHelp(std::cout);
    return 0;
  }
  else if (argc == 3 && !strcmp(argv[1], "--check"))
  {
    checkDictionary(argv[2], std::cout);
    return 0;
  }
  return 0;
}
