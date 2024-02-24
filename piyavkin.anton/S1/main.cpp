#include <iostream>
#include "list.hpp"

int main()
{
  using namespace piyavkin;
  List< int > list;
  try
  {
    list.push_front(5);
    list.push_front(50);
    list.push_front(500);
    std::cout << list.head_->value_ << ' ' << list.head_->next_->value_ << ' ' << list.head_->next_->next_->value_;
    list.pop_back();
    list.pop_back();
    list.pop_back();
    list.pop_back();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}
