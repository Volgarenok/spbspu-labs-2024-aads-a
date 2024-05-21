#include <iostream>
#include <fstream>
#include "tree.hpp"
#include "commands.hpp"
#include "input_data.hpp"
#include "key_summ.hpp"

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
  if (data.empty())
  {
    std::cerr << "<EMPTY>\n";
    return 1;
  }
  std::pair< int, std::string > pair;
  if (command == "ascending")
  {
    pair = ascend(data);
  }
  else if (command == "descending")
  {
    pair = descend(data);
  }
  else if (command == "breadth")
  {
    pair = breadth(data);
  }
  std::cout << pair.first << " " << pair.second;
  return 0;
}
