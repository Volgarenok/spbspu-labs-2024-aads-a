#include <iostream>
#include "list.hpp"

struct isPos {
  bool operator() (const int & value) { return (value > 0); }
};

int main()
{
  
  using namespace lebedev;
  List< int > list;
  list.push_back(10);
  List< int > listC(list);
  list.push_back(20);
  list.push_back(30);

  list.push_back(-10);
  list.push_back(25);
  list.push_back(-30);
  list.push_back(-40);

  List< int > list2(list);

  list2.remove_if(isPos());

  std::cout << "=============\n";
  list.outputList(std::cout);
  std::cout << "=============\n";
  list2.outputList(std::cout);
  return 0;
}
