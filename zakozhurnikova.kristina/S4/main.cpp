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

  mytree.push(2, "hjk");
  mytree.push(3, "m");
  mytree.push(1, "hello");
  mytree.push(0, "uhyyh");
  mytree.del(0);
  mytree.push(10, "uhyyh");
  mytree.push(15, "uhyyh");
  mytree.push(20, "uhyyh");
  mytree.push(30, "uhyyh");
  mytree.push(5, "uhyyh");
  mytree.push(8, "uhyyh");
  mytree.push(90, "uhyyh");
  mytree.push(65, "uhyyh");
  mytree.push(34, "uhyyh");
  mytree.push(23, "uhyyh");
  mytree.del(65);
  mytree.push(12, "uhyyh");
  mytree.push(80, "uhyyh");
  mytree.del(10);
  for (auto it = mytree.cbegin(); it != mytree.cend(); ++it)
  {
    std::cout << (*it).first << ' ' << (*it).second << '\n';
  }
  //  maps.push("zaz", std::move(mytree));
  return 0;
}
