#include <iostream>
#include <string>
#include "inputOutput.hpp"

int main()
{
  using namespace skuratov;
  using pair = std::pair< std::string, List< size_t > >;
  List< pair > sequences;
  try
  {
    inputAll(std::cin, sequences);
  }
  catch (const std::invalid_argument)
  {
    std::cout << 0 << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  outputAll(sequences, std::cout);
  return 0;
}
