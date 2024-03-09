#include <iostream>
#include "list.hpp"

int main()
{
  using namespace lebedev;
  List< int > list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_front(-10);
  list.clear();

  list.outputList(std::cout);
  std::cout << list.size() << '\n';
  std::cout << list.empty() << '\n';
  return 0;
}
