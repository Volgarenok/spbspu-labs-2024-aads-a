#include <iostream>
#include "list.hpp"

int main()
{
  using namespace grechishnikov;

  List< int > testList;
  testList.push_back(12);
  testList.push_back(13);
  testList.push_front(12313);
  testList.pop_back();
  testList.pop_front();

  std::cout << testList.empty() << '\n';
  testList.pop_front();
  std::cout << testList.empty() << '\n';

  testList.push_front(12313);
  testList.push_front(12313);
  List< int > testList2(testList);
  List< int > testList2p5(std::move(testList));

  List< int > testList3;
  List< int > testList4;
  testList3 = testList2;
  testList4 = std::move(testList2);
}
