#include <fstream>
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <limits>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <string>
#include "AVLtree.hpp"
#include "AVLtreeNode.hpp"
#include "commands.hpp"

using mainMap = novokhatskiy::Tree< std::string, novokhatskiy::Tree< size_t, std::string > >;
using map = novokhatskiy::Tree< size_t, std::string >;

void inputDict(mainMap& dict, std::istream& in)
{
  while (!in.eof())
  {
    in.clear();
    std::string name = {};
    in >> name;
    novokhatskiy::Tree< size_t, std::string> tmp;
    size_t key = {};
    while (in >> key)
    {
      std::string val = {};
      in >> val;
      tmp.insert({ key, val });
    }
    dict[name] = tmp;
    //dict.insert({ name, tmp });
  }
  in.clear();
}

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  Tree< std::string, Tree< size_t, std::string > > maps;
  if (argc != 2)
  {
    std::cerr << "Wrong input file\n";
    return 1;
  }
  else
  {
    std::fstream fileinp(argv[1]);
    inputDict(maps, fileinp);
  }
  using namespace std::placeholders;
  Tree< std::string, std::function< void(mainMap&, std::istream&, std::ostream&) > > commands;
  commands["print"] = std::bind(print, _1, _2, std::ref(std::cout));
  commands["complement"] = std::bind(complement, _1, _2, _3);
  commands["intersect"] = intersectCmd;
  commands["union"] = unionCmd;
  std::string command = {};
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(maps, std::cin, std::cout);
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}