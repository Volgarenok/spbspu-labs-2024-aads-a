#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"
#include "output.hpp"

int main()
{
  using namespace piyavkin;
//  size_t size = 0;
//  size_t max_size_list = 0;
//  std::pair< std::string, piyavkin::List< unsigned int >* >* pairs = nullptr;
//  try
//  {
//    pairs = inputList(std::cin, size, max_size_list);
//    output(std::cout, pairs, size, max_size_list);
//  }
//  catch (const std::exception& e)
//  {
//    std::cerr << e.what() << '\n';
//    return 1;
//  }
//  if (!pairs)
//  {
//    std::cout << 0;
//  }
//  std::cout << '\n';
//  delete[] pairs;
  List< int > list;
  size_t sum = 0;
  for (size_t i = 0; i < 5; ++i)
  {
    list.push_back(i);
  }
  for (size_t i = 0; i < 5; ++i)
  {
    list.out_val(std::cout, i, sum);
    std::cout << ' ';
  }
  std::cout << '\n';
  list.insert(++list.begin(), 10);
  for (size_t i = 0; i < 6; ++i)
  {
    list.out_val(std::cout, i, sum);
    std::cout << ' ';
  }
  std::cout << '\n';
  list.remove_if([](int n){ return n == 10; });
  for (size_t i = 0; i < 10; ++i)
  {
    list.out_val(std::cout, i, sum);
    std::cout << ' ';
  }
  std::cout << '\n';
}
