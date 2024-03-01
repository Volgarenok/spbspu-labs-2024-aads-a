#include <iostream>
#include "list.hpp"

int main()
{
  using namespace erohin;
  int a = 0;
  std::cin >> a;
  List< int > list;
  list.insert(a);
}
