#include <iostream>
#include "list.hpp"

int main()
{
  using namespace lebedev;
  List< int > list;
  list.push_back(10);
  List< int > listC(list);
  list.push_back(20);
  list.push_back(30);

  list.push_back(-10);
  list.push_back(-20);
  list.push_back(-30);
  list.push_back(-40);

  List< int > list2(list);


  std::cout << list.front() << "\n";
  std::cout << list.back() << "\n";
  std::cout << "=============\n";
  listC.outputList(std::cout);
  return 0;
}
