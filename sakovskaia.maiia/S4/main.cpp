#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <tree.hpp>
#include "input.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace sakovskaia;
  using NewTree = Tree< std::string, Tree< size_t, std::string > >;
  NewTree dictionaries;
  if (argc != 2)
  {
    std::cerr << "Error arg. comand line\n";
    return 1;
  }
  else
  {
    std::ifstream file(argv[1]);
    dictionaries = input(file);
  }

  using funcForPrint = std::function< void(NewTree &, std::istream &, std::ostream &) >;
  Tree< std::string, funcForPrint > printTree;
  printTree.push("print", print);
  using func = std::function< void(NewTree &, std::istream &) >;
  Tree< std::string, func > cmd;

  cmd.push("complement", complement);
  cmd.push("intersect", intersect);
  cmd.push("union", unionCMD);

  std::string inputCommand = "";

  while (std::cin >> inputCommand)
  {
    try
    {
      auto it = cmd.find(inputCommand);
      if (it != cmd.cend())
      {
        it->second(dictionaries, std::cin);
      }
      else
      {
        throw std::out_of_range("<INVALID COMMAND>");
      }
    }
    catch (const std::out_of_range &)
    {
      try
      {
        auto it = printTree.find(inputCommand);
        if (it != printTree.cend())
        {
          it->second(dictionaries, std::cin, std::cout);
        }
        else
        {
          throw std::out_of_range("<INVALID COMMAND>");
        }
      }
      catch (const std::out_of_range &)
      {
        std::cout << "<INVALID COMMAND>" << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
      catch (const std::logic_error & e)
      {
        std::cout << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::logic_error & e)
    {
      std::cout << e.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
