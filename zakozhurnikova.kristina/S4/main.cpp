#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include "binarySearchTree.hpp"
#include "comparator.hpp"
#include "inputMaps.hpp"
#include "treeNode.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  BinarySearchTree< std::string, BinarySearchTree< int, std::string > > maps;
  BinarySearchTree< int, std::string > mytree;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    inputMaps(file, maps);
  }
  else
  {
    std::cerr << "you didn't attach the file\n";
  }

  mytree.push(10, "hjk");
  mytree.push(9, "m");
  mytree.push(15, "hello");
  mytree.push(18, "uhyyh");
  mytree.push(8, "uhyyh");
  mytree.push(14, "uhyyh");
  mytree.push(7, "uhyyh");
  mytree.del(15);
  mytree.del(14);
  mytree.del(18);
  for (auto it = mytree.cbegin(); it != mytree.cend(); ++it)
  {
    std::cout << (*it).first << ' ' << (*it).second << '\n';
  }
  //  maps.push("zaz", std::move(mytree));
  return 0;
}
