#include "list.hpp"
#include <iostream>
#include "iterator.hpp"

int main()
{
  strelyaev::List< int > list;
  try
  {
    list.pop_back();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }
}
