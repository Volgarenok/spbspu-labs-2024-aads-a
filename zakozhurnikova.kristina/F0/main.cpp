#include <binarySearchTree.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include "commands.hpp"
#include "inputDictionary.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  using dict = BinarySearchTree< std::string, BinarySearchTree< std::string, List< std::string > > >;
  dict dictionary;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    inputDictionary(file, dictionary);
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }
  using namespace std::placeholders;
  BinarySearchTree< std::string, std::function< void(List< std::string >&) > > commands;

  commands["print"] = std::bind(print, _1, std::cref(dictionary));
  commands["intersect"] = std::bind(intersect, _1, std::ref(dictionary));
  commands["complement"] = std::bind(complement, _1, std::ref(dictionary));
  commands["specificLetter"] = std::bind(specificLetter, _1, std::ref(dictionary));
  commands["union"] = std::bind(doUnion, _1, std::ref(dictionary));
  commands["destruction"] = std::bind(destruction, _1, std::ref(dictionary));
  commands["elimination"] = std::bind(elimination, _1, std::ref(dictionary));
  commands["addition"] = std::bind(addition, _1, std::ref(dictionary));
  commands["palindrome"] = std::bind(palindrome, _1, std::ref(dictionary));
  commands["rider"] = std::bind(rider, _1, std::ref(dictionary));
  commands["interpreter"] = std::bind(interpreter, _1, std::ref(dictionary));

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      List< std::string > args;
      inputArgs(std::cin, args);
      commands.at(command)(args);
      args.clear();
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << "<INVALID INPUT>\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what();
      return 1;
    }
  }
}
