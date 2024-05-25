#include <algorithm>
#include <iostream>
#include <map>
#include <functional>
#include "shell_sort.hpp"
#include "selection_sort.hpp"
#include "generate_numbers.hpp"
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
    std::string sorting = argv[1];
    std::string type = argv[2];
    if (size == 0)
    {
      std::cerr << "Size should me more than zero\n";
      return 1;
    }
    if (type == "ints")
    {
      std::vector< int > vec = generateNumbers< int >(size);
      testSortings(std::cout, vec, vec.size(), sorting);
    }
    else if (type == "floats")
    {
      std::vector< float > vec = generateNumbers< float >(size);
      testSortings(std::cout, vec, vec.size(), sorting);
    }

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
