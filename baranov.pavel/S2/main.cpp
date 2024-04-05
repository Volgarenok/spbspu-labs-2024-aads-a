#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

int main()
{
  using namespace baranov;
  int a = 0;

  Stack< int > stack;
  Queue< int > queue;

  while (std::cin >> a)
  {
    stack.push(a);
    queue.push(a);
  }

  while (!stack.empty())
  {
  std::cout << stack.top() << '\n';
  stack.pop();
  }

  while (!queue.empty())
  {
  std::cout << queue.front() << '\n';
  queue.pop();
  }
}

