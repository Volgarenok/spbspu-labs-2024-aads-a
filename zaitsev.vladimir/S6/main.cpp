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
  std::map< std::pair< std::string, std::string >, std::function< void(std::ostream&, size_t) > >s;
  s[{"ints", "ascending"}] = sortirator< int, std::less< int > >;
  s[{"ints", "descending]"}] = sortirator< int, std::greater< int > >;
  s[{"floats", "ascending"}] = sortirator< float, std::less< float > >;
  s[{"floats", "descending"}] = sortirator< float, std::greater< float > >;
  constexpr size_t size = 10;
  try
  {
    s[{argv[2], argv[1]}](std::cout, std::stoull(argv[3]));
  }
  catch (const std::exception&)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  return 0;
}
