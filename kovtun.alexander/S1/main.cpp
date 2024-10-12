#include <iostream>
#include <cassert>

#include "list.hpp"

int main()
{
  kovtun::List< int > * list = new kovtun::List< int >();

  for (int i = 0; i < 5; ++i)
  {
    list->push_back(i);
  }

  for (auto it = list->cbegin(); it != list->cend(); ++it)
  {
    std::cout << *it << "\n";
  }

  list->pop_back();

  for (auto it = list->cbegin(); it != list->cend(); ++it)
  {
    std::cout << *it << "\n";
  }

  std::cout << list->empty() << "\n";
  list->clear();
  std::cout << list->empty();

  return 0;
}
