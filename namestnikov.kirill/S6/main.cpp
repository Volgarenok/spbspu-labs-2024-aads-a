#include <algorithm>
#include <iostream>
#include <functional>
#include <random>
#include <tree.hpp>
#include "shell_sort.hpp"
#include "selection_sort.hpp"
#include "test_sortings.hpp"

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  if (argc != 4)
  {
    std::cerr << "Wrong command line arguments\n";
    return 1;
  }
  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      std::cerr << "Size should me more than zero\n";
      return 1;
    }
    std::string sorting = argv[1];
    std::string type = argv[2];
    std::default_random_engine generator;
    Tree< std::pair< std::string, std::string >, std::function< void(std::ostream &, std::default_random_engine & generator) > > sortMap;
    {
      using namespace std::placeholders;
      sortMap[{"ascending", "ints"}] = std::bind(testSortings< int, std::less< int > >, _1, _2, size);
      sortMap[{"ascending", "floats"}] = std::bind(testSortings< float, std::less< int > >, _1, _2, size);
      sortMap[{"descending", "ints"}] = std::bind(testSortings< int, std::greater< int > >, _1, _2, size);
      sortMap[{"descending", "floats"}] = std::bind(testSortings< float, std::greater< int > >, _1, _2, size);
    }
    sortMap.at({sorting, type})(std::cout, generator);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
