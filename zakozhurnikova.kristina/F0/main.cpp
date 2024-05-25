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
  std::string result;
  using namespace std::placeholders;
  BinarySearchTree< std::string, std::function< void(List< std::string >&) > > commands;

  commands["print"] = std::bind(print, _1, std::ref(result), std::cref(dictionary));

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      List< std::string > args;
      inputArgs(std::cin, args);

      commands.at(command)(args);
      std::cout << result;
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what();
      return 1;
    }
  }
}
