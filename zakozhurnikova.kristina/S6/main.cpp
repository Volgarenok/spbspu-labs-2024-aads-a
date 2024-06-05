#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <list.hpp>
#include <list>
#include <map>
#include <string>
#include "generate.hpp"
#include "print.hpp"
#include "sorting.hpp"
#include "sortingSheets.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  if (argc != 4)
  {
    std::cerr << "No right argument";
    return 1;
  }
  std::string sort = argv[1];
  std::string type = argv[2];
  auto condition = sort + type;
  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "Why 0? The size must be greater than zero";
    return 1;
  }
  try
  {
    std::default_random_engine generator;
    using namespace std::placeholders;
    std::map< std::string, std::function< void(std::ostream&, size_t, std::default_random_engine&) > > commands;
    commands["ascendingints"] = fillContainer< int, std::less< int > >;
    commands["ascendingfloats"] = fillContainer< float, std::less< float > >;
    commands["descendingints"] = fillContainer< int, std::greater< int > >;
    commands["descendingfloats"] = fillContainer< float, std::greater< float > >;

    commands.at(condition)(std::cout, size, generator);
  }
  catch (const std::exception& e)
  {
    std::cout << "No right argument\n";
    return 1;
  }
}
