#include <iostream>
#include "inputList.hpp"

int main()
{
  using namespace isaychev;
  using myPair = std::pair< std::string, List< size_t > >;
  List< myPair > mainList;
  inputList(std::cin, mainList);
/*  List < int > l;
  for (int i = 0; i < 4; ++i)
  {
    int a = 0;
    std::cin >> a;
    l.push(a);
  }*/
}
