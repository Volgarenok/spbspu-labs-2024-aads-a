#include <fstream>
#include <iostream>
#include <functional>
#include "inputDataset.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  using command_map_t = BSTree< std::string, std::function< void(functor_t &) > >;

  map_t dataset;
  if (argc == 3)
  {
    std::fstream in(argv[2]);
    inputDataset(in, dataset);
  }
  else
  {
    std::cerr << "bad launch\n";
    return 1;
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
    std::cout << "<EMPTY>";
  }
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
