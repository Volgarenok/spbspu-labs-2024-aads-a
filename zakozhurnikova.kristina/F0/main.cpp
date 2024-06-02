#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <binarySearchTree.hpp>
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

  commands.push("print", std::bind(print, _1, std::ref(std::cout), std::cref(dictionary)));
  commands.push("intersect", std::bind(intersect, _1, std::ref(dictionary)));
  commands.push("complement", std::bind(complement, _1, std::ref(dictionary)));
  commands.push("specificLetter", std::bind(specificLetter, _1, std::ref(dictionary)));
  commands.push("union", std::bind(doUnion, _1, std::ref(dictionary)));
  commands.push("destruction",std::bind(destruction, _1, std::ref(dictionary)));
  commands.push("elimination", std::bind(elimination, _1, std::ref(dictionary)));
  commands.push("addition", std::bind(addition, _1, std::ref(dictionary)));
  commands.push("palindrome", std::bind(palindrome, _1, std::ref(dictionary)));
  commands.push("rider", std::bind(rider, _1, std::ref(dictionary)));
  commands.push("interpreter", std::bind(interpreter, _1, std::ref(dictionary)));
  commands.push("save", std::bind(save, _1, std::cref(dictionary)));
  commands.push("addDictionary", std::bind(doAddDictionary, _1, std::ref(std::cin), std::ref(dictionary)));

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      List< std::string > args;
      if (command != "addDictionary")
      {
        inputArgs(std::cin, args);
      }
      commands.at(command)(args);
      args.clear();
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << "<INVALID INPUT>\n";
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
}
