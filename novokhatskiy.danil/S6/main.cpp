#include <algorithm>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <AVLtree.hpp>
#include "sortAndPrintSequence.hpp"

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
      throw std::invalid_argument("Size can't be zero");
    }
    Tree< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream&) > > sorts;
    srand(time(nullptr));
    sorts[{ "ints", "ascending" }] = sortSeq< int, std::less< int > >;
    sorts[{ "floats", "ascending" }] = sortSeq< float, std::less< float > >;
    sorts[{ "ints", "descending" }] = sortSeq< int, std::greater< int > >;
    sorts[{ "floats", "descending" }] = sortSeq< float, std::greater< float > >;
    std::string cmp = argv[1];
    std::string type = argv[2];
    sorts.at({ type, cmp })(size, std::cout);
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
