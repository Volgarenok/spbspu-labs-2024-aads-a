#include <iostream>
#include <stdexcept>
#include <forward_list>
#include <list>
#include <algorithm>
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
    doSortCommand< int >(std::cout, size, std::less< int >{});
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
