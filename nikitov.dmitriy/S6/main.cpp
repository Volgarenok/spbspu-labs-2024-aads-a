#include <iostream>
#include <deque>
#include <forward_list>
#include <algorithm>
#include <iomanip>
#include <list.hpp>
#include "sortings.hpp"
#include "iterators_functions.hpp"
#include "sort_sequence.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  if (argc != 4)
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  size_t size = std::stoull(argv[3]);
  if (size == 0)
  {
    std::cerr << "Error: Wrong size parameter" << '\n';
    return 1;
  }

  std::string sorting = argv[1];
  std::string type = argv[2];
  if (type == "ints")
  {
    sortSequence< int >(sorting, type, size);
  }
  else if (type == "floats")
  {
    sortSequence< float >(sorting, type, size);
  }
  else
  {
    std::cerr << "Error: Wrong type parameter" << '\n';
    return 1;
  }
  return 0;
}
