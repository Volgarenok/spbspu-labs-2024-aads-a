#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "myTree.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Bad input data!\n";
    return 1;
  }
  std::ifstream file(argv[1]);

  using dictionary = rebdev::AVLTree< long long int, std::string >;
  rebdev::AVLTree< std::string, dictionary > dictionaryTree;
  while (!file.eof())
  {
    std::string line;
    std::getline(file, line);
    std::stringstream inLine(line);
    inLine >> line;
    dictionary newDictionary;
    while (!inLine.eof())
    {
      int key;
      std::string value;
      inLine >> key;
      inLine >> value;
      newDictionary[key] = value;
    }

    dictionaryTree[line] = newDictionary;
  }
  return 0;
}
