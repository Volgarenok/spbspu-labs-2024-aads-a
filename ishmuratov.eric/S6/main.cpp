#include <iostream>
#include <functional>
#include <map>
#include <iomanip>

#include "generate.hpp"

int main(int argc, char * argv[])
{
  using namespace ishmuratov;

  if (argc != 4)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }

  size_t size;
  try
  {
    size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::underflow_error("Size of 0!");
    }
  }
  catch (const std::underflow_error & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::invalid_argument &)
  {
    std::cerr << "Incorrect size value!\n";
    return 1;
  }

  std::map< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream &, std::mt19937 &) > > cmds;
  {
    using namespace std::placeholders;
    cmds[std::make_pair("ascending", "ints")] = test_sort< int, std::less< int > >;
    cmds[std::make_pair("descending", "ints")] = test_sort< int, std::greater< int > >;
    cmds[std::make_pair("ascending", "floats")] = test_sort< float, std::less< float > >;
    cmds[std::make_pair("descending", "floats")] = test_sort< float, std::greater< float > >;
  }
  try
  {
    std::random_device device;
    std::mt19937 range(device());
    std::cout << std::fixed << std::setprecision(1);
    cmds[std::make_pair(argv[1], argv[2])](size, std::cout, range);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
