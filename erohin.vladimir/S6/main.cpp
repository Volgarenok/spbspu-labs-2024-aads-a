#include <iostream>
#include <stdexcept>
#include <forward_list>
#include <list>
#include <algorithm>
#include "sequence_operations.hpp"

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
    std::forward_list< int > random_seq;
    generate_random< int >(random_seq, size);
    random_seq.sort();
    std::copy(
      random_seq.cbegin(),
      random_seq.cend(),
      std::ostream_iterator< int >(std::cout, "\n")
    );
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
