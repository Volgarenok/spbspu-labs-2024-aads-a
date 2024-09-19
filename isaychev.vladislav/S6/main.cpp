#include <functional>
#include <tree/tree.hpp>
#include <iostream>
#include <iomanip>
#include "do_cmd.hpp"

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    return 1;
  }

  size_t amount = strtoull(argv[3], nullptr, 10);
  if (amount == 0)
  {
    return 2;
  }

  using namespace isaychev;
  BSTree< std::pair< std::string, std::string >, std::function< void(std::ostream &, size_t) > > commands;
  commands[{"ascending", "ints"}] = do_cmd< int, std::less< int > >;
  commands[{"ascending", "floats"}] = do_cmd< float, std::less< float > >;
  commands[{"descending", "ints"}] = do_cmd< int, std::greater< int > >;
  commands[{"descending", "floats"}] = do_cmd< float, std::greater< float > >;

  std::cout << std::fixed << std::setprecision(1);
  try
  {
    commands.at({argv[1], argv[2]})(std::cout, amount);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 3;
  }
}
