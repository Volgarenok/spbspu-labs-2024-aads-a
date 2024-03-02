#include <iostream>
#include "forward_list.hpp"
#include "iterators.hpp"
#include "node.hpp"

int main()
{
  using namespace namestnikov;
  ForwardList<int> Fwd;
  Fwd.push_front(1);
  Fwd.push_front(2);
  Fwd.pop_front();
}
