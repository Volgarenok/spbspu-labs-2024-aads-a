#include <iostream>
#include <fstream>
#include <functional>
#include <tree/tree.hpp>
#include "inputTree.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace baranov;
  if (argc != 3)
  {
    std::cerr << "Invalid CLA\n";
    return 1;
  }

  std::ifstream file(argv[2]);
  if (!file.is_open())
  {
    std::cerr << "Invalid file name\n";
    return 1;
  }
  Tree< int, std::string > tree;
  inputTree(file, tree);

  Tree< std::string, std::function< void(std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["ascending"] = std::bind(ascending, _1, std::cref(tree));
  }
  std::string cmd(argv[1]);
  try
  {
    cmds.at(cmd)(std::cout);
    std::cout << '\n';
  }
  catch (const std::exception &)
  {
    std::cout << "<INVALID COMMAND>";
  }
}

