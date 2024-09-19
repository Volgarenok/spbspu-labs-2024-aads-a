#include <fstream>
#include <iostream>
#include <functional>
#include "inputDataset.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  using command_map_t = BSTree< std::string, std::function< void(functor_t &) > >;

  std::fstream in;
  if (argc == 3)
  {
    in.open(argv[2]);
  }
  else
  {
    std::cerr << "bad launch\n";
    return 1;
  }

  map_t dataset;
  try
  {
    inputDataset(in, dataset);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 3;
  }

  command_map_t commands;
  {
    using namespace std::placeholders;
    commands["ascending"] = std::bind(trav_asc, std::ref(dataset), _1);
    commands["descending"] = std::bind(trav_des, std::ref(dataset), _1);
    commands["breadth"] = std::bind(trav_brd, std::ref(dataset), _1);
  }

  if (dataset.empty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    try
    {
      functor_t f;
      commands.at(argv[1])(f);
      std::cout << f.get_keysum() << f.get_valsum() << "\n";
    }
    catch (const std::exception &)
    {
      std::cerr << "<INVALID COMMAND>\n";
      return 2;
    }
  }
}
