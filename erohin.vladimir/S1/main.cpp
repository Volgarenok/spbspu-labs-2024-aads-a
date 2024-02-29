#include <iostream>
#include "node.hpp"

int main()
{
  using namespace erohin;
  int a = 0;
  std::cin >> a;
  Node< int > * head = nullptr;
  head = new Node< int >{ 0, nullptr };
  head->next_ = new Node< int >{ a, nullptr };
  std::cout << head->data_ << " " << head->next_->data_ << "\n";
}
