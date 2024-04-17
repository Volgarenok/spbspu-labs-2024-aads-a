#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }
  return 0;
}
