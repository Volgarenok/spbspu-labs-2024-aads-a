#include <iostream>
#include <forward_list>
#include <deque>
#include "bdlist.hpp"

#include "merge_sort.hpp"
#include "quick_sort.hpp"

int main()
{
  using namespace ishmuratov;

  List< int > bilist;
  bilist.pushBack(20);
  bilist.pushBack(4);
  bilist.pushBack(3);
  bilist.pushBack(12);
  bilist.pushBack(11);
  bilist.pushBack(50);

  merge_sort(bilist.begin(), bilist.end());
  for (auto value : bilist)
  {
    std::cout << value << " ";
  }
}
