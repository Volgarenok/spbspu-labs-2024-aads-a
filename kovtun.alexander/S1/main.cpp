#include <iostream>
#include <cassert>

#include "list.hpp"

int main()
{
  kovtun::List< int > * list = new kovtun::List< int >();

  auto b = list->cbegin();
  auto c = list->cend();

  std::cout << &c << *b;

  return 0;
}
