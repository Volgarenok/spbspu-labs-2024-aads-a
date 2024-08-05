#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <AVLTree.hpp>
#include "cmd.hpp"
#include "input.hpp"

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  using namespace sivkov;
  using avlTree = AVLTree< std::string, AVLTree< std::string, std::string > >;
  avlTree treeOfdic;

  if (argc != 2)
  {
    std::cerr << "Command line error\n";
    return 1;
  }

  if (std::string(argv[1]) == "help")
  {
    help(std::cout);
  }
  else
  {
    std::ifstream file(argv[1]);
    if (!file)
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
    treeOfdic = inputDictionary(file);
  }

  std::string command;

  using funcForPrint = std::function< void(avlTree&, std::istream&, std::ostream&) >;
  AVLTree< std::string, funcForPrint > outCommands;
  outCommands.push("list_words", list_words);
  outCommands.push("search_words", search_words);
  outCommands.push("repeating_words", repeating_words);
  outCommands.push("count", count_words);

  using func = std::function< void(avlTree&, std::istream&) >;
  AVLTree< std::string, func > cmd;
  cmd.push("add_word", add_word);
  cmd.push("add_translation", add_translation);
  cmd.push("create", create_dictionary);
  cmd.push("remove_word", remove_word);
  cmd.push("delete_dictionary", delete_dictionary);
  cmd.push("rename_dictionary", rename_dictionary);
  cmd.push("merge", merge_dictionaries);

  std::string inputCommand = "";

  while (std::cin >> inputCommand)
  {
    try
    {
      auto it = cmd.find(inputCommand);
      if (it != cmd.cend())
      {
        it->second(treeOfdic, std::cin);
      }
      else
      {
        auto itPrint = outCommands.find(inputCommand);
        if (itPrint != outCommands.cend())
        {
          itPrint->second(treeOfdic, std::cin, std::cout);
        }
        else
        {
          throw std::out_of_range("Invalid command");
        }
      }
    }
    catch (const std::out_of_range& e)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  try
  {
    save(treeOfdic, argv[1]);
  }
  catch (const std::logic_error& e)
  {
    std::cerr << "Error saving file: " << e.what() << "\n";
  }

  return 0;
}

