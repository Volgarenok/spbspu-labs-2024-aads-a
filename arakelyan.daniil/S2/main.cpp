#include <iostream>

#include "queue.hpp"
#include "stack.hpp"

int main()
{
  using namespace arakelyan;
  using stack_struct = Stack< size_t, BinList< size_t > >;
  stack_struct myStack;
  myStack.push(5);
  std::cout << myStack.top() << "\n";
  myStack.push(10);
  std::cout << myStack.top() << "\n";
  std::cout << myStack.size() << " - size \n";
  std::cout << myStack.empty() << " empty\n";
  stack_struct otherStack(myStack);
  std::cout << "otherStack size = " << otherStack.size() << "\n";
  return 0;
}
