#include <iostream>
#include <forward_list>
#include <deque>
#include "bdlist.hpp"

#include "sort.hpp"

int main()
{
  using namespace ishmuratov;
  std::forward_list< int > forwardList;
  std::deque< int > deque;
  List< int > biList;

  biList.pushBack(1);
  biList.pushBack(2);
  biList.pushBack(3);
  biList.pushBack(4);
  biList.pushBack(5);
  biList.pushBack(6);
  biList.pushBack(7);
  biList.pushBack(8);
  biList.pushBack(9);
  biList.pushBack(10);

  Iterator< int > end = biList.begin();
  for (int i = 0; i != biList.size() - 1; ++i)
  {
    end++;
  }

  quick_sort(biList.begin(), end, std::less< int >());
  for (auto node = biList.begin(); node != biList.end(); ++node)
  {
    std::cout << *node << " ";
  }

}
