#include <iostream>
#include "list.hpp"

int main()
{
  using namespace piyavkin;
  List< int > list;
  list.push_back(5);
  list.push_back(50);
  list.push_back(500);
  std::cout << list.head_->value_ << ' ' << list.head_->next_->value_ << ' ' << list.head_->next_->next_->value_;
}
