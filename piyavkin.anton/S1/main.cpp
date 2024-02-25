#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"

int main()
{
  using namespace piyavkin;
  List< int > list;
  for (size_t i = 1; i < 5; ++i)
  {
    list.push_back(i);
  }
  auto it = list.begin();
  list.insert(++it, 0);
  std::cout << list.head_->next_->next_->value_;
//  std::pair< std::string, piyavkin::List< unsigned int >* >* pairs = nullptr;
//  try
//  {
//    pairs = inputList(std::cin);
//  }
//  catch (const std::exception& e)
//  {
//    std::cerr << e.what() << '\n';
//    return 1;
//  }
//  if (!pairs)
//  {
//    std::cout << 0 << '\n';
//  }
//  delete[] pairs;
}
