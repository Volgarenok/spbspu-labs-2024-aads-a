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
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  if (sequences.empty())
  {
    std::cout << 0 << '\n';
    return 0;
  }

  try
  {
    outputAll(sequences, std::cout);
  }
  catch (const std::overflow_error&)
  {
    std::cerr << "Overflow" << '\n';
    return 1;
  }
  return 0;
}
