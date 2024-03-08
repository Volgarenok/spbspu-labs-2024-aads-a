#include "list.hpp"
#include "inputList.hpp"
#include <iostream>

int main()
{
  using namespace baranov;
  List< std::pair< std::string, List< size_t > > > list;
  inputList(std::cin, list);
}

