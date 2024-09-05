#include <map>
#include <iomanip>
#include <utility>
#include <functional>

#include "sortprocessing.hpp"
#include "sorts.hpp"

int main(int argc, char *argv[])
{
  using namespace gladyshev;
  if (argc != 4)
  {
    std::cerr << "bad data\n";
    return 1;
  }
  size_t size = 0;
  try
  {
    size = std::stoull(argv[3]);
  }
  catch (...)
  {
    std::cerr << "Wrong parametr\n";
    return 1;
  }
  if (size == 0)
  {
    std::cerr << "Wrong size\n";
    return 1;
  }
  std::map< std::pair< std::string, std::string >, std::function< void(size_t, std::ostream&) > > cmds;
  cmds[std::make_pair("ascending", "floats")] = processSorts< float, std::less< float > >;
  cmds[std::make_pair("descending", "floats")] = processSorts< float, std::greater< float > >;
  cmds[std::make_pair("ascending", "ints")] = processSorts< int, std::less< int > >;
  cmds[std::make_pair("descending", "ints")] = processSorts< int, std::greater< int > >;
  std::cout << std::fixed << std::setprecision(1);
  try
  {
    cmds.at(std::make_pair(std::string(argv[1]), std::string(argv[2])))(size, std::cout);
  }
  catch (...)
  {
    std::cerr << "Error\n";
    return 1;
  }
}
