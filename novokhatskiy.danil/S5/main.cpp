#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <AVLtree.hpp>
#include "SumStruct.hpp"
#include "commands.hpp"

void inputMaps(std::istream& in, novokhatskiy::Tree< int, std::string >& map)
{
  while (in)
  {
    in.clear();
    int key{};
    std::string val;
    while (in >> key >> val)
    {
      map.insert(std::make_pair(key, val));
    }
    if (!in.eof())
    {
      throw std::overflow_error("Error input");
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
    try
    {
      std::ifstream inFile(argv[2]);
      inputMaps(inFile, map);
    }
    catch (const std::overflow_error&)
    {
      std::cerr << "Overflow\n";
      return 1;
    }
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
