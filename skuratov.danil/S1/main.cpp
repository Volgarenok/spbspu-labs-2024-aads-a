#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


int main()
{
  using inputIterT = std::istream_iterator< int >;
  std::vector< int > data(inputIterT{std::cin}, inputIterT{});

  using outputIterT = std::ostream_iterator< int >;
  std::copy(data.cbegin(), data.cend(), outputIterT{std::cout, "\n"});
}
