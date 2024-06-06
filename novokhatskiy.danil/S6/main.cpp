#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include "sortAndPrintSequence.hpp"
#include "sortings.hpp"

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  try
  {
    if (argc != 4)
    {
      std::cerr << "Wrong input arguments\n";
      return 1;
    }
    size_t size = std::stoull(argv[3]);
    if (size <= 0)
    {
      throw std::invalid_argument("Zero size");
    }
    std::string sort(argv[1]);
    std::string type(argv[2]);
    if (type == "ints")
    {
      sortSeq< int >(sort, type, size, std::cout);
    }
    else if (type == "floats")
    {
      sortSeq< float >(sort, type, size, std::cout);
    }
    else
    {
      throw std::invalid_argument("Invalid type of sequence");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
