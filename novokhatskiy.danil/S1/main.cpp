#include <iostream>
#include "list.hpp"
#include "iterator.hpp"

int main()
{
  using namespace novokhatskiy;
  List<double> a1;
  double b = 10;
  a1.push_front(b);
  a1.push_front(100);
  a1.push_front(55);
  List<double> a2;
  a2.push_front(33);
  a2.push_front(44);
  a1.swap(a2);
  a1.print();
}
