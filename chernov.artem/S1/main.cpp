#include <iostream>
#include "node.hpp"
#include "forwardList.hpp"
#include "inputList.hpp"
#include "outputList.hpp"

int main()
{
  using namespace chernov;
  List< namedNumberedList > list;
  inputLists(std::cin, list);
  outNames(list, std::cout);
  return 0;
}
