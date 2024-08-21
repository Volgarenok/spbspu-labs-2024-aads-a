#include <iostream>
#include <fstream>

#include "binarySearchTree.hpp"
#include "readingFromFile.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Invalid args\n";
    return 1;
  }
  using namespace belokurskaya;
  BinarySearchTree< int, std::string > tree;

  try
  {
    std::ifstream file(argv[2]);
    readingFromFile(file, tree);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  using func = std::function< void(int&, std::string&, BinarySearchTree< int, std::string >&) >;
  BinarySearchTree< std::string, func > commands;
  commands["ascending"] = ascending;
  commands["descending"] = descending;
  commands["breadth"] = breadth;

  try
  {
    int num{};
    std::string str;
    commands.at(argv[1])(num, str, tree);
    std::cout << num << str << '\n';
  }
  catch (const std::overflow_error&)
  {
    std::cerr << "Overflow\n";
    return 1;
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "<INVALID ARGUMENT>\n";
    return 1;
  }
  catch (const std::logic_error&)
  {
    std::cout << "<EMPTY>\n";
  }
}
