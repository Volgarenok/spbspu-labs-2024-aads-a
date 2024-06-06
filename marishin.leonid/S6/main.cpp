#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "generate.hpp"
#include "print.hpp"
#include "sorting.hpp"
#include "sortingList.hpp"
#include <linkedList.hpp>

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
    using namespace std::placeholders;
    std::map< std::pair< std::string, std::string >, std::function< void(std::ostream&, size_t, std::default_random_engine&) > > commands;
    commands[{"ascending", "ints"}] = fillContainer< int, std::less< int > >;
    commands[{"ascending", "floats"}] = fillContainer< float, std::less< float > >;
    commands[{"descending", "ints"}] = fillContainer< int, std::greater< int > >;
    commands[{"descending", "floats"}] = fillContainer< float, std::greater< float > >;

    commands.at(std::make_pair(argv[1], argv[2]))(std::cout, size, generator);
  }
  catch (...)
  {
    std::cout << "Error\n";
    return 1;
  }
}
