#include <iostream>
#include <forward_list>
#include <deque>
#include <random>
#include <functional>
#include "bdlist.hpp"

#include "merge_sort.hpp"
#include "quick_sort.hpp"

int main()
{
  using namespace ishmuratov;

  std::random_device device;
  std::mt19937 range(device());
  std::uniform_int_distribution< int > dist(-10000, 10000);

  List< int > bilist_merge;
  std::deque< int > deque_qsort;
  std::forward_list< int > forward_sort;

  for (size_t i = 0; i < 10; ++i)
  {
    int num = dist(range);
    bilist_merge.pushBack(num);
    deque_qsort.push_back(num);
    forward_sort.push_front(num);
  }

  merge_sort(bilist_merge.begin(), bilist_merge.end(), std::greater< int >());
  quick_sort(deque_qsort.begin(), deque_qsort.end(), std::greater< int >());
  forward_sort.sort(std::greater< int >());

  for (auto value: bilist_merge)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";

  for (auto value: deque_qsort)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";

  for (auto value: forward_sort)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";
}
