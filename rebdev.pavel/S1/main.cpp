#include <iostream>
#include <utility>

#include "listFunction.hpp"
//#include "biList.hpp"
#include <list> //del

int main()
{
  rebdev::pairList listOfPairs; //corr

  try
  {
    using namespace rebdev;
    inputList(std::cin, listOfPairs);
    nameAndListOfNumList pair{createNameList(listOfPairs), createListOfNumList(listOfPairs)};
    outputList(std::cout, pair);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
