#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <map>
#include "read_dictionaries.hpp"
#include "tree.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;

  Tree< int, size_t > tree;
  tree.insert({1, 3});
  std::map< std::string, std::map< size_t, std::string > > treeOfDictionaries;
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    readDictionaries(treeOfDictionaries, input);
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  return 0;
}
