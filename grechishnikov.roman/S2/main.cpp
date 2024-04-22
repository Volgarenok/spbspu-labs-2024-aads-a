#include "iostream"
#include "stack.hpp"

int main()
{
  using namespace grechishnikov;
  Stack< int > s1;
  s1.push(10);
  s1.push(20);
  std::cout << s1.top() << '\n';
  s1.pop();
  std::cout << s1.top() << '\n';
}
