#include <iostream>
#include "list.hpp"
#include "inputList.hpp"
#include "listFunctions.hpp"
#include "outputFunctions.hpp"

int main()
{
  using namespace baranov;
  try
  {
    List< std::pair< std::string, List< size_t > > > sequences;

    inputList(std::cin, sequences);
    if (sequences.empty())
    {
      std::cout << 0 << '\n';
      return 0;
    }

    printNames(std::cout, sequences);

    List< List < size_t > > numbers;
    readByElement(numbers, sequences);
    printLists(std::cout, numbers);

    printSums(std::cout, numbers);
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what();
    return 1;
  }
}

