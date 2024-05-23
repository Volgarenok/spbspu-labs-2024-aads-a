#include <iostream>
#include <functional>
#include <string>
#include <map>
#include "executor.hpp"

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }
  std::map< std::pair< std::string, std::string >, std::function< void(std::ostream&, size_t) > >sorter_types;
  sorter_types[{"ints", "ascending"}] = sortirator< int, std::less< int > >;
  sorter_types[{"ints", "descending"}] = sortirator< int, std::greater< int > >;
  sorter_types[{"floats", "ascending"}] = sortirator< float, std::less< float > >;
  sorter_types[{"floats", "descending"}] = sortirator< float, std::greater< float > >;
  try
  {
    size_t size = std::stoull(argv[3]);
    if (!size)
    {
      throw std::invalid_argument("");
    }
    sorter_types.at({argv[2], argv[1]})(std::cout, size);
  }
  catch (const std::exception&)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  return 0;
}
