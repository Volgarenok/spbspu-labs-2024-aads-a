#include "list.hpp"
#include "inputList.hpp"
#include "listFunctions.hpp"
#include "outputFunctions.hpp"
#include <iostream>

int main()
{
  using namespace baranov;
  List< std::pair< std::string, List< size_t > > > sequences;
  inputList(std::cin, sequences);
  printNames(std::cout, sequences);

  List< List < size_t > > numbers;
  readByElement(numbers, sequences);
  printLists(std::cout, numbers);
}

