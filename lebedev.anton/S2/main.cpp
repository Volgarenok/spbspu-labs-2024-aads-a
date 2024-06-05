#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

int main()
{
  using namespace lebedev;
  Queue< int > stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);
  std::cout << stack.front() << '\n';
  std::cout << stack.back() << '\n';
  stack.pop();
  std::cout << stack.front() << '\n';
  std::cout << stack.back() << '\n';
  std::cout << stack.empty() << '\n';
  std::cout << stack.size() << '\n';
}
