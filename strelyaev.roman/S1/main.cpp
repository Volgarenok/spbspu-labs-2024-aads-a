#include "list.hpp"
#include <iostream>
#include "iterator.hpp"

int main()
{
  strelyaev::Iterator< int > a;
  try
  {
    a++;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }
}
