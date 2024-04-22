#include "iostream"
#include "stack.hpp"

int main()
{
  using namespace grechishnikov;
  Stack< int > s1;
  s1.push(10);
  s1.push(20);
  Stack< int > s2(s1);
  std::cout << s2.top() << '\n';
  s2.pop();
  std::cout << s2.top() << '\n';
  Stack< int > s3(std::move(s1));
  std::cout << s3.top() << '\n';
  s3.pop();
  std::cout << s3.top() << '\n';
}
