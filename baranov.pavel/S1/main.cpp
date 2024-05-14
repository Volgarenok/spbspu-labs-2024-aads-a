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
    std::cout << '\n';

    List< List < size_t > > numbers;
    readByElement(numbers, sequences);
    if (!numbers.empty())
    {
      printLists(std::cout, numbers);
      std::cout << '\n';
    }

    printSums(std::cout, numbers);
    std::cout << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what();
    return 1;
  }
}

