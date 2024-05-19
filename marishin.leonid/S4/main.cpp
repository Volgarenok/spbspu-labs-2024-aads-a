#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <BinarySearchTree.hpp>

int main(int argc, char *argv[])
{
  using namespace marishin;
  using map = BinarySearchTree< int, std::string >;
  BinarySearchTree< std::string, map > maps;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    inputMaps(in, maps);
  }
  else
  {
    std::cerr << "Wrong command line arguments\n";
    return 1;
  }

  BinarySearchTree< std::string, std::function< void(std::istream&, maps&) > > commands;
  {
    using namespace std::placeholders;
    commands.add("print", &print);
    commands.add("union", &doUnion);
    commands.add("complement", &complement)
    commands.add("intersect", &intersect);
  }
  std::string commandName = "";
  while (std::cin >> commandName)
  {
    try
    {
      command(std::cin, commandName);
      if (!commandName.empty())
      {
        std::cout << commandName << '\n';
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what();
      return 1;
    }
  }
}
