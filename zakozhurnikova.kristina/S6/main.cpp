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
  auto condition = std::make_pair(sort, type);
  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "Why 0? The size must be greater than zero";
    return 1;
  }
  try
  {
    using namespace std::placeholders;
    std::map< std::pair< std::string, std::string >, std::function< void(const std::string&, size_t) > > commands;
    commands[std::make_pair("ascending", "ints")] =
      std::bind(sortAndPrint< int, std::less< int > >, _1, _2, std::less< int >());
    commands[std::make_pair("ascending", "floats")] =
      std::bind(sortAndPrint< float, std::less< float > >, _1, _2, std::less< float >());
    commands[std::make_pair("descending", "ints")] =
      std::bind(sortAndPrint< int, std::greater< int > >, _1, _2, std::greater< int >());
    commands[std::make_pair("descending", "floats")] =
      std::bind(sortAndPrint< float, std::greater< float > >, _1, _2, std::greater< float >());

    commands.at(condition)(type, size);
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cout << "No right argument\n";
    return 1;
  }
}
