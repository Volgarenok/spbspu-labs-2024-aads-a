#include <iostream>
#include <string>
#include "list.hpp"
#include "inputOutput.hpp"

int main()
{
  using namespace skuratov;
  try
  {
    inputOutput();
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << 0 << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
