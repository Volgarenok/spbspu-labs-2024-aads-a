#include <iostream>
#include <fstream>
#include <tree.hpp>

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }
  std::string command = argv[1];
  try
  {
    std::ifstream file(argv[2]);
  }
  catch (...)
  {
    std::cerr << "Error while reading from file!";
    return 1;
  }
  std::cout << command;
  return 0;
}
