#include <iostream>
#include <cassert>

#include "list.hpp"

int main()
{
  kovtun::List< int > * list = new kovtun::List< int >();
  kovtun::List< int > * list2 = new kovtun::List< int >();

  for (int i = 0; i < 10; ++i)
  {
    list->push_front(i);
    list2->push_front(10-i);
  }

  for (auto it = list->cbegin(); it != list->cend(); ++it)
  {
    std::cout << *it << "\n";
  }

  list->swap(*list2);

  for (auto it = list->cbegin(); it != list->cend(); ++it)
  {
    std::cout << *it << "\n";
  }

  return 0;
}
