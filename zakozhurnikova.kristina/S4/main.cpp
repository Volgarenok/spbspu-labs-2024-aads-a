#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include "treeNode.hpp"
#include "binarySearchTree.hpp"
#include "comparator.hpp"
#include "inputMaps.hpp"

int main(int argc, char *argv[])
{
  using namespace zakozhurnikova;
  BinarySearchTree< std::string, BinarySearchTree< int, std::string > > maps;
  BinarySearchTree<int, std::string> mytree;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    inputMaps(file, maps);
  }
  else
  {
    std::cerr << "you didn't attach the file";
  }

  mytree.push(2, "hjk");
  mytree.push(3, "m");
  mytree.push(1, "hello");
  mytree.push(0, "uhyyh");
  for (auto it = mytree.cbegin(); it != mytree.cend(); ++it)
  {
    std::cout << (*it).first << ' ' << (*it).second << '\n';
  }
  maps.push("zaz", std::move(mytree));
  return 0;

}
