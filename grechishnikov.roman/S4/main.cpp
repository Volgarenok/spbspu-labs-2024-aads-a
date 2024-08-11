#include <iostream>
#include <functional>
#include "treeNode.hpp"
#include "constTreeIterator.hpp"
int main()
{
  using namespace grechishnikov;
  using namespace grechishnikov::detail;
  Node< int, int > n1(1, 1, nullptr, nullptr, nullptr);
  Node< int, int > n2(2, 2, &n1, nullptr, nullptr);
  Node< int, int > n3(3, 3, &n2, nullptr, nullptr);
  Node< int, int > n4(4, 4, &n3, nullptr, nullptr);
  ConstTreeIterator< int, int, std::less< int > > iter_n(&n4);
  iter_n--;
  std::cout << iter_n->first << '\n';

  Node< int, int > d2(2, 2, nullptr, nullptr, nullptr);
  Node< int, int > d1(1, 1, &d2, nullptr, nullptr);
  Node< int, int > d3(3, 3, &d2, nullptr, nullptr);
  Node< int, int > d5(5, 5, &d3, nullptr, nullptr);
  Node< int, int > d4(4, 4, &d5, nullptr, nullptr);
  d2.left_ = &d1;
  d5.left_ = &d4;
  d3.right_ = &d5;
  ConstTreeIterator< int, int, std::less< int > > iter_d(&d4);
  iter_d--;
  std::cout << iter_d->first << '\n';
}
