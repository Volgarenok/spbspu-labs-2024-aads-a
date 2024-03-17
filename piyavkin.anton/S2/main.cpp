#include <iostream>
#include "stack.hpp"

int main()
{
  using namespace piyavkin;
  Stack< char > stack;
  char a = 0;
  char b = 0;
  std::cin >> a >> b;
  stack.push(a);
  stack.push(b);
  std::cout << stack.list.front() << ' ' << stack.list.back();
  stack.pop();
  stack.pop();
  std::cout << stack.empty();
}
