#include <iostream>
#include "stack.hpp"

int main()
{
  using namespace lebedev;
  Stack< int > stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);
  std::cout << stack.top() << '\n';
  stack.pop();
  std::cout << stack.top() << '\n';
  std::cout << stack.empty() << '\n';
  std::cout << stack.size() << '\n';
}
