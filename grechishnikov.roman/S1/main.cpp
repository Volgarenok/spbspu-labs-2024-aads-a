#include <iostream>
#include "list.hpp"

void pr(size_t sth)
{
  std::cout << sth << " ";
}

int main()
{
  using namespace grechishnikov;

  List< size_t > testListIter;
  testListIter.push_front(1);
  testListIter.push_front(2);
  testListIter.push_front(3);
  testListIter.push_front(4);
  testListIter.push_front(5);

  auto it = testListIter.begin();
  it++;
  testListIter.assign(it, testListIter.end());

  std::for_each(testListIter.begin(), testListIter.end(), pr);
  std::cout << '\n';

  List< size_t > testListInit;
  testListInit.assign({ 1, 2, 4, 6, 7, 9 });
  std::for_each(testListInit.begin(), testListInit.end(), pr);
  std::cout << '\n';

}
