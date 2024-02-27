#include <iostream>
#include <cassert>

#include "iterator.hpp"
#include "list.hpp"

int main()
{
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  assert(list.begin() != list.end());
  list.pop_back();
  auto it = list.begin();
  assert((*it) == 1);
  list.pop_front();
  it = list.begin();
  assert((*it) == 2);
  list.clear();
  assert(list.empty());
  std::cout << "Nice\n";
  return 0;
}

