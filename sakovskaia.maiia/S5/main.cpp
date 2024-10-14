#include <iostream>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <tree.hpp>
#include "commands.hpp"
#include "key_sum.hpp"

int main(int argc, char * argv[])
{
  using namespace sakovskaia;
  using newTree = Tree< int, std::string >;
  newTree tree;
  std::string command = "";
  std::string filename = "";
  if (argc != 3)
  {
    std::cerr << "<INPUT ERROR>\n";
    return 1;
  }
  command = argv[1];
  filename = argv[2];
  using func = std::function< void(newTree &, KeySum &, std::ostream &)>;

  Tree< std::string, func > commands;
  commands.push("ascending", ascending);
  commands.push("descending", descending);
  commands.push("breadth", breadth);
  try
  {
    std::fstream file(filename);
    input(tree, file);
    auto it = commands.find(command);
    KeySum f;
    if (it != commands.cend())
    {
      it->second(tree, f, std::cout);
    }
    else
    {
      throw std::out_of_range("<ERROR COMMAND>");
    }
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error & e)
  {
    std::cout << e.what() << "\n";
  }
  return 0;
}
