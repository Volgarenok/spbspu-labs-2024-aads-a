#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <functional>
#include "AVLTree.hpp"
#include "cmd.hpp"
#include "input.hpp"

int main(int argc, char* argv[])
{
  using namespace sivkov;
  using avlTree = AVLTree< std::string, AVLTree< std::string, std::string > >;
  avlTree treeOfdic;
  if (argc != 2)
  {
    std::cerr << "Error CMD line\n";
    return 1;
  }
  else
  {
    std::ifstream file(argv[1]);
    treeOfdic = inputDictionary(file);
  }

  std::string command;

  while (std::cin >> command)
  {
    if (command == "addWord")
    {
      add_word(treeOfdic, std::cin);
    }
    else if (command == "addTr")
    {
      add_translation(treeOfdic, std::cin);
    }
    else if (command == "save")
    {
      save(treeOfdic, argv[1]);
    }
  }

  return 0;
}
