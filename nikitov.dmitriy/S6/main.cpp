#include <iostream>
#include <tree.hpp>
#include "sort_sequence.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  if (argc != 4)
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("Error: Wrong size parameter");
    }

    Tree< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream&) > > types;
    types[{ "ints", "ascending" }] = sortSequence< int, std::less< int > >;
    types[{ "floats", "ascending" }] = sortSequence< float, std::less< float > >;
    types[{ "ints", "descending" }] = sortSequence< int, std::greater< int > >;
    types[{ "floats", "descending" }] = sortSequence< float, std::greater< float > >;

    std::string sorting = argv[1];
    std::string type = argv[2];
    types.at({ type, sorting })(size, std::cout);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
