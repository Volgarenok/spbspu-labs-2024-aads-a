#include <iostream>
#include "forward_list.hpp"
#include "forward_list_iterators.hpp"

int main()
{
  using namespace novokhatskiy;
  ForwardList<int> l;
  for (size_t i = 0; i < 10; i++)
  {
    l.push_front(i);
  }
  ForwardList<int> l2(l);
  for (auto i = l2.begin(); i != l2.end(); i++)
  {
    std::cout << *i << ' ';
  };
  l2.reverse();
  for (auto i = l2.begin(); i != l2.end(); i++)
  {
      std::cout << *i << ' ';
  };
}
