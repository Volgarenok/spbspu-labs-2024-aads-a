#include <iostream>
#include <cstddef>
#include <string>
#include <functional>
#include <utility>
#include <map>
#include <list/list.hpp>
#include "sortings.hpp"
#include "testSortings.hpp"
#include "generate.hpp"

int main(int argc, char * argv[])
{
  using namespace baranov;
  if (argc < 4)
  {
    std::cerr << "Incorrect CLA\n";
    return 1;
  }
  try
  {
    std::string direction = argv[1];
    std::string type = argv[2];
    std::string params = direction + type;
    size_t size = std::atoi(argv[3]);
    if (size == 0)
    {
      throw std::logic_error("Invalid size");
    }

    std::map< std::string, std::function< void(std::ostream &, size_t) > > commands;
    commands["ascendingints"] = testSortings< int, std::less< int > >;
    commands["descendingints"] = testSortings< int, std::greater< int > >;
    commands["ascendingfloats"] = testSortings< float, std::less< float > >;
    commands["descendingfloats"] = testSortings< float, std::greater< float > >;

    commands.at(params)(std::cout, size);
    std::cout << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

