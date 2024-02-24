#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"

int main()
{
  using namespace piyavkin;
  std::pair< std::string, piyavkin::List< unsigned int >* >* pairs = nullptr;
  try
  {
    pairs = inputList(std::cin);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  delete[] pairs;
}
