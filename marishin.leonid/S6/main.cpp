#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <linkedList.hpp>
#include "print.hpp"
#include "sorting.hpp"
#include "sortingList.hpp"


int main(int argc, char* argv[])
{
  std::srand(std::time(0));
  using namespace marishin;
  if (argc != 4)
  {
    std::cerr << "No right argument";
    return 1;
  }
  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "must be greater than 0";
    return 1;
  }
  try
  {
    std::map< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream&) > > cmd;
    cmd[{"ascending", "ints"}] = sortAndPrint< int, std::less< int > >;
    cmd[{"ascending", "floats"}] = sortAndPrint< float, std::less< float > >;
    cmd[{"descending", "ints"}] = sortAndPrint< int, std::greater< int > >;
    cmd[{"descending", "floats"}] = sortAndPrint< float, std::greater< float > >;

    cmd.at(std::make_pair(argv[1], argv[2]))(size, std::cout);
  }
  catch (...)
  {
    std::cout << "Error\n";
    return 1;
  }
}
