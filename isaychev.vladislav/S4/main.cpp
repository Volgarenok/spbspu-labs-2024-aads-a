#include <iostream>
#include <fstream>
#include <limits>
#include "commands.hpp"
#include "inputDictionaries.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  using command_map_t = BSTree< std::string, std::function< void(std::istream &) > >;

  BSTree< std::string, BSTree< int, std::string > > dictionaries;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    inputDictionaries(in, dictionaries);
  }
  else
  {
    std::cerr << "troubles with filename\n";
    return 1;
  }

  command_map_t commands;
  {
    using namespace std::placeholders;
    commands["print"] = std::bind(print, std::cref(dictionaries), std::ref(std::cout), _1);
    commands["complement"] = std::bind(complement, std::ref(dictionaries), _1);
    commands["intersect"] = std::bind(intersect, std::ref(dictionaries), _1);
    commands["union"] = std::bind(unite, std::ref(dictionaries), _1);
  }

  std::string str;
  while (!std::cin.eof())
  {
    std::cin >> str;
    if (!str.empty())
    {
      try
      {
        (commands.at(str))(std::cin);
      }
      catch (const std::runtime_error & e)
      {
        std::cout << e.what() << "\n";
      }
      catch (const std::exception &)
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    str.clear();
  }
  /*BSTree< int, std::string > tree;
  tree[7] = "g";
  tree[3] = "c";
  tree[1] = "a";
  tree[2] = "b";
  tree[5] = "e";
  tree[4] = "d";
  tree[10] = "l";
  tree[6] = "f";
  tree[12] = "n";
  tree[8] = "h";
  tree[9] = "k";
  tree[11] = "m";

  BSTree< int, std::string > tree2;
  tree2 = tree;

  auto i = tree.cbegin();
  std::cout << (*i).first << "\n";*/
}
