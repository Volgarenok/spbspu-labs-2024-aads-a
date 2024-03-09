#include <iostream>
#include "list.hpp"
#include "inputList.hpp"

void pr(size_t sth)
{
  std::cout << sth << " ";
}

void prList(grechishnikov::namedList list)
{
  std::for_each(list.second.begin(), list.second.end(), pr);
}

bool ch(size_t sth)
{
  if (sth % 2 == 0)
  {
    return true;
  }
  return false;
}

int main()
{
  using namespace grechishnikov;

//  namedList testListInput = inputList(std::cin);
//  std::for_each(testListInput.second.begin(), testListInput.second.end(), pr);
//git test
  List< namedList > testListInput2 = inputLists(std::cin);
  std::for_each(testListInput2.begin(), testListInput2.end(), prList);
  std::cout << countSum(testListInput2.begin()->second);


}
