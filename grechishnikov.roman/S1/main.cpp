#include <iostream>
#include "list.hpp"

int main()
{
  using namespace grechishnikov;
  List< int > testList;
  testList.push_back(12);
  testList.push_back(13);

  List< int > testList2(testList);
}
