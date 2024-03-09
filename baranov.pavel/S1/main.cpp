#include "list.hpp"
#include "inputList.hpp"
#include "listFunctions.hpp"
#include "outputFunctions.hpp"
#include <iostream>

int main()
{
  using namespace baranov;
  List< std::pair< std::string, List< size_t > > > list;
  inputList(std::cin, list);

  printNames(std::cout, list);

  List< List < size_t > > numbers;
  readByElement(numbers, list);
}

