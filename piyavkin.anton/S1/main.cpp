#include <iostream>
#include "list.hpp"
#include "inputlist.hpp"
#include "output.hpp"

int main()
{
  using namespace piyavkin;
  // list_t list;
  // try
  // {
  //   inputList(std::cin, list);
  //   output(std::cout, list);
  // }
  // catch (const std::invalid_argument& e)
  // {
  //   std::cout << 0 << '\n';
  //   return 0;
  // }
  // catch (const std::exception& e)
  // {
  //   std::cerr << e.what() << '\n';
  //   return 1;
  // }
  // std::cout << '\n';
  List<int> list(3,3u);
  list.remove(3);
  size_t i  = 0;
  auto it = list.cbegin();
  while (i != list.size())
  {
    std::cout << *it++ << ' ';
    ++i;
  }
}
