#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include "SumStruct.hpp"
#include "commands.hpp"
#include "AVLtree.hpp"

void inputMaps(std::istream& in, novokhatskiy::Tree< int, std::string >& map)
{
  while (!in.eof())
  {
    in.clear();
    int key{};
    std::string val;
    while (in >> key >> val)
    {
      map.insert(std::make_pair(key, val));
    }
  }
}

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  Tree< int, std::string > map;
  if (argc != 3)
  {
    std::cerr << "Wrong input parameters\n";
    return 1;
  }
  else
  {
    std::ifstream inFile(argv[2]);
    inputMaps(inFile, map);
  }
  Tree< std::string, std::function< void(int&, std::string&, Tree< int, std::string >&) > > commands;
  commands["ascending"] = ascending;
  commands["descending"] = descending;
  commands["breadth"] = breadth;
  try
  {
    int num{};
    std::string str;
    commands.at(argv[1])(num, str, map);
    std::cout << num << str << '\n';
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "<INVALID ARGUMENT>\n";
  }
  catch (const std::logic_error& e)
  {
    std::cout << e.what() << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
