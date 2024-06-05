#include <iostream>
#include <fstream>
#include <string>
#include <tree.hpp>
#include "commands.hpp"
#include "sum_keys.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  Tree< int, std::string > dictionary;
  if (argc == 3)
  {
    std::ifstream input(argv[2]);
    int key = {};
    std::string value = {};
    while (input >> key >> value)
    {
      dictionary.insert({ key, value });
    }
    if (!input.eof())
    {
      std::cerr << "Error: Wrong input" << '\n';
      return 2;
    }
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  Tree< std::string, std::function< void(const Tree< int, std::string >&, SumKeys& f) > > commands;
  commands["ascending"] = traverseAscending;
  commands["descending"] = traverseDescending;
  commands["breadth"] = traverseBreadth;

  try
  {
    SumKeys f;
    commands.at(argv[1])(dictionary, f);
    std::cout << f.getKey() << f.getLine() << '\n';
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }
  catch (const std::logic_error&e)
  {
    std::cout << e.what() << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
