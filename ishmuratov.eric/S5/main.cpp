#include <iostream>
#include <fstream>
#include <functional>
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
    std::cerr << "Error while reading from file!\n";
    return 1;
  }

  AVLTree< std::string, std::function< std::pair< int, std::string >(AVLTree< int, std::string > &) > > cmds;
  cmds.insert(std::make_pair("ascending", ascend));
  cmds.insert(std::make_pair("descending", descend));
  cmds.insert(std::make_pair("breadth", breadth));
  std::pair< int, std::string > pair;
  try
  {
    pair = cmds.at(command)(data);
    std::cout << pair.first << pair.second << '\n';
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "Command wasn't found!\n";
    return 1;
  }
  catch (const std::logic_error & e)
  {
    std::cout << e.what() << '\n';
    return 0;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
