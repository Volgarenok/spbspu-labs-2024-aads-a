#include <iostream>
#include "list.hpp"

int main()
{
  using namespace lebedev;
  List< int > list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  list.push_back(-10);
  list.push_back(-20);
  list.push_back(-30);
  list.push_back(-40);

  std::cout << list.front() << "\n";
  std::cout << list.back() << "\n";
  std::cout << "=============\n";
  list.outputList(std::cout);
  return 0;
}
