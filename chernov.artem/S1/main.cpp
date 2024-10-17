#include <iostream>
#include "node.hpp"
#include "forwardList.hpp"
#include "inputList.hpp"
#include "outputList.hpp"

int main()
{
  using namespace chernov;
  using namedNumberedList = std::pair< std::string, List< size_t > >;
  List< namedNumberedList > list;
  List< size_t > listSums;
  inputLists(std::cin, list);
  if (list.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }
  try
  {
    outNames(list, std::cout);
    outNumbers(list, listSums, std::cout);
    if (listSums.isEmpty())
    {
      std::cout << "0\n";
      return 0;
    }
    else
    {
      outSums(listSums, std::cout);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
