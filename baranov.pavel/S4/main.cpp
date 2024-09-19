#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <tree/tree.hpp>
#include "inputTrees.hpp"
#include "commands.hpp"

int main(int argc, char ** argv)
{
  using namespace baranov;
  if (argc != 2)
  {
    std::cerr << "Invalid CLA\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Invalid file name\n";
    return 1;
  }
  using basicTree = Tree< int, std::string >;
  using treeOfTrees = Tree< std::string, basicTree >;
  treeOfTrees trees;
  inputTrees(trees, file);

  Tree< std::string, std::function< void(std::istream &, std::ostream &) > > commands;
  {
    using namespace std::placeholders;
    commands.insert("print", std::bind(print, std::cref(trees), _1, _2));
    commands.insert("complement", std::bind(complement, std::ref(trees), _1, _2));
    commands.insert("intersect", std::bind(intersect, std::ref(trees), _1, _2));
    commands.insert("union", std::bind(unite, std::ref(trees), _1, _2));
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

