#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <map>
#include "inputTree.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Invalid CLA\n";
    return 1;
  }
  using namespace baranov;
  std::map< int, std::string > tree;
  try
  {
    std::ifstream file(argv[2]);
    inputTree(file, tree);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }

  std::map< std::string, std::function< void(std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["ascending"] = std::bind(ascending, _1, std::ref(tree));
  }
  std::string cmd(argv[1]);
  cmds.at(cmd)(std::cout);
}

