#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

int main()
{
  using namespace piyavkin;
  Queue< char > stack;
  char a = 0;
  char b = 0;
  std::cin >> a >> b;
  stack.push(a);
  stack.push(b);
  std::cout << stack.list.front() << ' ' << stack.list.back() << ' ';
}
