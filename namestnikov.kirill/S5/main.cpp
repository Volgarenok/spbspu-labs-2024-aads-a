#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <fstream>
#include <tree.hpp>
#include "sum_func.hpp"
#include "commands.hpp"
#include "input_dict.hpp"

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  Tree< int, std::string > myMap;
  if (argc == 3)
  {
    std::ifstream file(argv[2]);
    if (!file.is_open())
    {
      std::cerr << "Can not open file\n";
      return 1;
    }
    try
    {
      myMap = inputDict(file);
    }
    catch (...)
    {
      std::cerr << "Wrong input\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Wrong count of command line parameters\n";
    return 1;
  }
  Tree< std::string, std::function< void(int &, std::string &, Tree< int, std::string > &) > > commands;
  commands["ascending"] = ascending;
  commands["descending"] = descending;
  commands["breadth"] = breadth;
  try
  {
    std::string output = "";
    int result = 0;
    commands.at(argv[1])(result, output, myMap);
    std::cout << result << output << "\n";
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "Wrong command name\n";
    return 1;
  }
  catch (const std::logic_error & e)
  {
    std::cout << "<EMPTY>\n";
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
