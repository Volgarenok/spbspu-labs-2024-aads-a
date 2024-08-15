#include <iostream>
#include <fstream>
#include <string>

#include "binarySearchTree.hpp"

int main(int argc, char* argv[])
{
  using namespace belokurskaya;

  using Dictionary = BinarySearchTree< int, std::string >;
  using DictionaryCollection = BinarySearchTree< std::string, Dictionary >;
  if (argc != 2)
  {
    std::cerr << "No args\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }
  DictionaryCollection dictionaries;
  std::string line;

  while (std::getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }
  }
  using fun = std::function< void(DictionaryCollection&, const std::string&, const std::string&, const std::string&) >;

  BinarySearchTree< std::string, fun > cmds;
  {
    using namespace std::placeholders;
    cmds["complement"] = std::bind(&complement, _1, _2, _3, std::placeholders::_4);
    cmds["intersect"] = std::bind(&intersect, _1, _2, _3, _4);
    cmds["union"] = std::bind(&unionDictionaries, _1, _2, _3, _4);
  }
}
