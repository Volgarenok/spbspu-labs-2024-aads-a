#include <iostream>
#include "list.hpp"

int main()
{
  using namespace lebedev;
  List< int > list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  List< int > list2;
  list2.push_back(-10);
  list2.push_back(-20);
  list2.push_back(-30);
  list2.push_back(-40);

  list.swap(list2);

  list.outputList(std::cout);
  std::cout << list.size() << '\n';
  std::cout << list.empty() << '\n';
  return 0;
}
