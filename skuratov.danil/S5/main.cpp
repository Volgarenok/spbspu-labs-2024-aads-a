#include <iostream>
#include <fstream>
#include <functional>
#include "UBST.hpp"
#include "treeTraversalCmds.cpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  UBST< int, std::string > data;
  if (argc > 1)
  {
    std::string cmd = argv[1];
    std::ifstream filename(argv[2]);
    if (!filename)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }

    int keyNum = {};
    while (filename >> keyNum)
    {
      std::string value = {};
      filename >> value;
      data.insert(keyNum, value);
    }
  }
  else
  {
    std::cerr << "Not enough arguments" << '\n';
    return 2;
  }

  UBST< std::string, std::function< std::pair< int, std::string >(UBST< int, std::string >&) > > cmds;
  using namespace std::placeholders;
  cmds["ascending"] = std::bind(isAscending, _1);
  cmds["descending"] = std::bind(isDescending, _1);
  cmds["breadth"] = std::bind(isBreadth, _1);

  return 0;
}
