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
    std::default_random_engine generator;
    std::map< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream&, std::default_random_engine & generator) > > commands;
    commands[{"ascending", "ints"}] = sortAndPrint< int, std::less< int > >;
    commands[{"ascending", "floats"}] = sortAndPrint< float, std::less< float > >;
    commands[{"descending", "ints"}] = sortAndPrint< int, std::greater< int > >;
    commands[{"descending", "floats"}] = sortAndPrint< float, std::greater< float > >;

    commands.at(std::make_pair(argv[1], argv[2]))(size, std::cout, generator);
  }
  catch (...)
  {
    std::cout << "Error\n";
    return 1;
  }
}
