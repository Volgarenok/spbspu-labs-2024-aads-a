#include <iostream>
#include "stack.hpp"
#include "queue.hpp"
#include "tokenType.hpp"

int main()
{
  using namespace grechishnikov;
  Queue< int > a;
  a.push(10);
  a.push(20);
  std::cout << a.size() << '\n';

  Stack< int > b;
  b.push(10);
  b.push(20);
  std::cout << b.size() << '\n';

}
