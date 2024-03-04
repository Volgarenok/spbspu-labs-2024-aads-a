#include <iostream>
#include "list.hpp"

void pr(size_t sth)
{
  std::cout << sth << " ";
}

int main()
{
  using namespace grechishnikov;

  List< int > testListSwap1;
  List< int > testListSwap2;

  testListSwap1.push_front(1);
  testListSwap2.push_front(2);
  testListSwap1.swap(testListSwap2);
  std::cout << "F: " << testListSwap1[0] << " " << "S: " << testListSwap2[0] << '\n';

  List< int > testListIter;
  testListIter.push_front(1);
  testListIter.push_front(2);
  testListIter.push_front(3);
  testListIter.push_front(4);
  testListIter.push_front(5);

  std::cout << std::for_each(testListIter.begin(), testListIter.end(), pr) << '\n';
}
