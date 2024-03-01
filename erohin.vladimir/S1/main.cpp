#include <iostream>
#include "list.hpp"

int main()
{
  using namespace erohin;
  List< int > list;
  int elem = 0;
  while (std::cin >> elem)
  {
    list.insert(elem);
  }
  auto iter = list.begin();
  while (iter != list.end())
  {
    std::cout << *(iter++) << "\n";
  }
}
