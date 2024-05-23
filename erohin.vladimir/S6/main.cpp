#include <iostream>
#include <stdexcept>
#include <forward_list>
#include <list>
#include <functional>
#include "red_black_tree.hpp"
#include "sort_command.hpp"

int main(int argc, char ** argv)
{
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
    sort_case.insert(std::make_pair(std::make_pair("ascending", "ints"), doSortCommand< int, std::less< int >));
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
