#include <iostream>
#include "list.hpp"

int main()
{
  using namespace erohin;
  List< int > list;
  int elem = 0;
  while (std::cin >> elem)
  {
    list.push_front(elem);
  }
  List< int > other_list(list);
  auto iter = other_list.begin();
  while (iter != other_list.end())
  {
    std::cout << *(iter++) << "\n";
  }
}
