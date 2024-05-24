#include <iostream>
#include <map>
#include <fstream>
#include <functional>
#include <limits>

#include "cmd.hpp"
#include "iodata.hpp"
#include "tree.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  using namespace ishmuratov;
  data_t data;
  input_dict(data, file);

  AVLTree< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds.insert(std::make_pair("print", std::bind(cmd::print, std::ref(data), _1, _2)));
    cmds.insert(std::make_pair("complement", std::bind(cmd::complement, std::ref(data), _1)));
    cmds.insert(std::make_pair("intersect", std::bind(cmd::intersect, std::ref(data), _1)));
    cmds.insert(std::make_pair("union", std::bind(cmd::uniond, std::ref(data), _1)));
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::underflow_error &)
    {
      std::cout << "<EMPTY>\n";
    }
    catch (const std::runtime_error & e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
    }
  }
}
