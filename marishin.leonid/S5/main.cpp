#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <functional>
#include <limits>
#include <binarySearchTree.hpp>
#include "command.hpp"
#include "sumFunc.hpp"
#include "inputMaps.hpp"

int main(int argc, char * argv[])
{
  using namespace marishin;
  Tree< int, std::string > myMap;
  if (argc == 3)
  {
    std::ifstream in(argv[2]);
    if (!in.is_open())
    {
      std::cerr << "Can not open the file\n";
      return 1;
    }
    try
    {
      myMap = inputMaps(in);
    }
    catch (...)
    {
      std::cerr << "Incorrect input\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Wrong command line arguments\n";
    return 2;
  }
  Tree< std::string, std::function< void(int &, std::string &, Tree< int, std::string > &) > > commands;
  commands["ascending"] = ascending;
  commands["descending"] = descending;
  commands["breadth"] = breadth;
  int res = 0;
  try
  {
    std::string out = "";
    commands.at(argv[1])(res, out, myMap);
    std::cout << res << out << "\n";
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "<INVALID COMMAND>\n";
    return 1;
  }
  catch (const std::logic_error &)
  {
    std::cout << "<EMPTY>\n";
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
