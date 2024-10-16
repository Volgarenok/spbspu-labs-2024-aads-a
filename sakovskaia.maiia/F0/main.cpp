#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "commands.hpp"
#include <tree.hpp>

int main(int argc, char* argv[])
{
  using namespace sakovskaia;
  using NewTree = Tree< std::string, Tree< std::string, size_t > >;
  NewTree dictionaries;
  if (argc == 2)
  {
    if (std::string(argv[1]) == "--help")
    {
      printHelp(std::cout);
      return 0;
    }
    else
    {
      try
      {
        dictionaries = inputCMD(std::string(argv[1]));
      }
      catch (...)
      {
        std::cerr << "<ERROR>";
        return 1;
      }
    }
  }
  using funcForPrint = std::function< void(NewTree &, std::istream &, std::ostream &) >;
  Tree < std::string, funcForPrint > cmd;
  cmd.push("new", newCmd);
  cmd.push("delete", deleteCmd);
  cmd.push("load", loadCmd);
  cmd.push("add", addCmd);
  cmd.push("save", saveCmd);
  cmd.push("remove", removeCmd);
  cmd.push("frequency", frequencyCmd);
  cmd.push("update", updateCmd);
  cmd.push("combining", combiningCmd);
  cmd.push("diff", diffCmd);

  std::string inputCommand = "";
  while (std::cin >> inputCommand)
  {
    try
    {
      auto itPrint = cmd.find(inputCommand);
      if (itPrint != cmd.cend())
      {
        itPrint->second(dictionaries, std::cin, std::cout);
      }
      else
      {
        throw std::out_of_range("<INVALID COMMAND>");
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
  return 0;
}
