#include <vector>
#include <iostream>
#include <string>
#include <forward_list>
#include "list.hpp"
#include "iterator.hpp"

int main()
{
  using namespace novokhatskiy;
  List<double> a1;
  double b = 10;
  a1.push_front(b);
  a1.push_front(100);
  a1.pop_front();
  std::cout << a1.front();
  a1.push_front(55);
}
