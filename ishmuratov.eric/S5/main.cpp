#include <iostream>
#include <fstream>
#include "tree.hpp"
#include "commands.hpp"
#include "input_data.hpp"

int main(int argc, char * argv[])
{
  using namespace ishmuratov;
  AVLTree< int, std::string > data;
  if (argc != 3)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }
  std::string command = argv[1];
  try
  {
    std::ifstream file(argv[2]);
    input_data(data, file);
  }
  catch (...)
  {
    std::cerr << "Error while reading from file!";
    return 1;
  }
  data.print(std::cout);
  return 0;
}
