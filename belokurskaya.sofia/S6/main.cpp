#include <iostream>
#include <map>
#include <functional>

#include "list.hpp"
#include "sortings.hpp"
#include "doSort.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid args\n";
    return 1;
  }
  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "Invalid size\n";
    return 1;
  }
  std::srand(std::time(0));

  using namespace belokurskaya;
  std::map< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream&) > > commands;
  commands[{"ascending", "ints"}] = sortAndPrint< int, std::less< int > >;
  commands[{"ascending", "floats"}] = sortAndPrint< float, std::less< float > >;
  commands[{"descending", "ints"}] = sortAndPrint< int, std::greater< int > >;
  commands[{"descending", "floats"}] = sortAndPrint< float, std::greater< float > >;
}
