#include <iostream>
#include <cassert>

#include "list.hpp"

int main()
{
  kovtun::List< int > * list = new kovtun::List< int >();

  for (int i = 0; i < 10; ++i)
  {
    list->push_front(i);
  }

  for (auto it = list->cbegin(); it != list->cend(); ++it)
  {
    std::cout << *it << "\n";
  }

  list->pop_front();

  for (auto it = list->cbegin(); it != list->cend(); ++it)
  {
    std::cout << *it << "\n";
  }

  std::cout << list->empty() << "\n";
  list->clear();
  std::cout << list->empty();

  return 0;
}
