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

    std::string sorting = argv[1];
    std::string type = argv[2];
    Tree< std::string, std::function< void(std::string, std::string, size_t, std::ostream&) > > types;
    types["ints"] = sortSequence< int >;
    types["floats"] = sortSequence< float >;
    types.at(type)(sorting, type, size, std::cout);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
