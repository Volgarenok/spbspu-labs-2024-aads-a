#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include "red_black_tree.hpp"
#include "sort_command.hpp"

int main(int argc, char ** argv)
{
  std::srand(std::time(0));
  using namespace erohin;
  if (argc != 4)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("Invalid sequence size");
    }
    using sort_func_cmd = std::function< void(std::ostream &) >;
    RedBlackTree< std::pair< std::string, std::string >, sort_func_cmd > sort_case;
    {
      using namespace std::placeholders;
      sort_case[{ "ascending", "ints" }] = std::bind(doSortCommand< int, std::less< int > >, _1, size);
      sort_case[{ "descending", "ints" }] = std::bind(doSortCommand< int, std::greater< int > >, _1, size);
      sort_case[{ "ascending", "floats" }] = std::bind(doSortCommand< float, std::less< float > >, _1, size);
      sort_case[{ "descending", "floats" }] = std::bind(doSortCommand< float, std::greater< float > >, _1, size);
    }
    std::cout << std::setprecision(1) << std::fixed;
    sort_case.at({ argv[1], argv[2] })(std::cout);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
