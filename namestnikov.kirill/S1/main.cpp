#include <iostream>
#include "forward_list.hpp"
#include "iterators.hpp"
#include "node.hpp"
#include "input_output_lists.hpp"

int main()
{
  using namespace namestnikov;
  ForwardList<int> Fwd;
  for (int i = 0; i < 10; ++i)
  {
    Fwd.push_front(i);
  }
  std::cout << Fwd.size();
  Fwd.print();
  ForwardIterator<int> p = Fwd.begin();
  ForwardIterator<int> q = Fwd.end();

  for (auto i = Fwd.begin(); i != Fwd.end(); ++i)
  {
    std::cout << *i << " ";
  }
}
