#include <iostream>

#include "queue.hpp"
#include "stack.hpp"

int main()
{
  using namespace arakelyan;
  using myQueue = Queue< size_t, BinList< size_t > >;
  myQueue mainQ;
  mainQ.push(5);
  mainQ.push(10);
  mainQ.push(15);
  std::cout << mainQ.front() << "\n";
  std::cout << mainQ.back() << "\n";
  mainQ.pop();
  std::cout << mainQ.front() << "\n";
  myQueue otherQ(mainQ);
  std::cout << otherQ.size() << "\n";
  std::cout << otherQ.empty() << "\n";
  return 0;
}
