#include <iostream>
#include "iterator.hpp"
#include "list.hpp"

int main()
{
  using namespace nikitov;
  std::cout << "good";
  List< int > list;
  list.push_back(3);
  list.push_back(4);
  std::cout << list.size();
  list.pop_back();
  std::cout << list.size();
}
