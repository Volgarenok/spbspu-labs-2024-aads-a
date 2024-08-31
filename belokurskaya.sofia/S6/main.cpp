#include <iostream>
#include <map>
#include <functional>

#include "list.hpp"
#include "sortings.hpp"

int main(int argc, char* argv[])
{
  std::srand(std::time(0));
  if (argc != 4)
  {
    std::cerr << "Invalid args\n";
    return 1;
  }
  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "Invalid size\n";
    return 1;
  }
  std::map< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream&) > > commands;
}
