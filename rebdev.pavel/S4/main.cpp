#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

#include "myTree.hpp"
#include "functions.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Bad input data!\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  using dictTree = rebdev::AVLTree< long long int, std::string >;
  rebdev::AVLTree< std::string, dictTree > dictionaryTree;
  while (!file.eof())
  {
    std::string line;
    std::getline(file, line);
    if (line.empty())
    {
      continue;
    }
    std::stringstream inLine(line);
    inLine >> line;
    dictTree newDictionary;
    dictionaryTree[line] = newDictionary;
    while (!inLine.eof())
    {
      int key;
      std::string value;
      inLine >> key;
      inLine >> value;
      (dictionaryTree[line])[key] = value;
    }
  }
  rebdev::AVLTree< std::string, std::function< dictTree(const dictTree &, const dictTree &) > > commandTree;
  commandTree["complement"] = rebdev::complement;
  commandTree["intersect"] = rebdev::intersect;
  commandTree["union"] = rebdev::treeUnion;
  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    try
    {
      if (command == "print")
      {
        std::cin >> command;
        auto it = dictionaryTree.find(command);
        std::cout << command;
        rebdev::print(std::cout, (*it).second);
      }
      else
      {
        auto it = commandTree.find(command);
        std::string firstTree, secondTree;
        std::cin >> command >> firstTree >> secondTree;
        auto tree1 = dictionaryTree.find(firstTree);
        auto tree2 = dictionaryTree.find(secondTree);
        dictionaryTree[command] = ((*it).second((*tree1).second, (*tree2).second));
      }
    }
    catch (const std::exception & e)
    {
      if (!std::cin.eof())
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
  return 0;
}
