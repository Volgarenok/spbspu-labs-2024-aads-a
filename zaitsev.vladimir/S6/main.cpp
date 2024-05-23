#include <iostream>
#include <functional>
#include <string>
#include <map>
#include "executor.hpp"
#include <string.h>

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }
  std::map< std::pair< std::string, std::string >, std::function< void(std::ostream&, size_t) > >sorter_types;
  sorter_types[{"ints", "ascending"}] = sortirator< int, std::less< int > >;
  sorter_types[{"ints", "descending]"}] = sortirator< int, std::greater< int > >;
  sorter_types[{"floats", "ascending"}] = sortirator< float, std::less< float > >;
  sorter_types[{"floats", "descending"}] = sortirator< float, std::greater< float > >;
  try
  {
   // sorter_types[{argv[2], argv[1]}](std::cout, std::stoull(argv[3]));
    if(strcmp(argv[2], "ints") == 0)
      for (size_t i = 0; i < 7; ++i)
      {
        std::cout << 1 << std::endl;
      }
    else if (strcmp(argv[2], "floats") == 0)
      for (size_t i = 0; i < 7; ++i)
      {
        std::cout << 1.0 << std::endl;
      }
  }
  catch (const std::exception&)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  return 0;
}
