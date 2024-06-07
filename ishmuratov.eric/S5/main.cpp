#include <iostream>
#include <fstream>
#include <tree.hpp>
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
    std::cout << "<EMPTY>\n";
    return 0;
  }
  std::pair< int, std::string > pair;
  try
  {
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
    else
    {
      std::cerr << "Incorrect command!\n";
      return 1;
    }
    std::cout << pair.first << pair.second << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
