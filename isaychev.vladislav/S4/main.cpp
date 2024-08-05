#include <iostream>
#include <fstream>
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
    try
    {
      (commands.at(str))(std::cin);
    }
    catch (const std::exception & e)
    {
      std::cout << e.what() << "\n";
    }
  }
/*  BSTree< int, std::string > tree;
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

  auto i = tree.begin();
  for (int a = 0; a < 6; ++a)
  {
    ++i;
  }
  std::cout << (*i).first << "\n";
  auto n = tree.erase(i);
  std::cout << (*n).first << "\n";*/
}
