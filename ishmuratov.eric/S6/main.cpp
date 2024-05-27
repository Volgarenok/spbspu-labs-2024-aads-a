#include <iostream>
#include <list>
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
  std::deque< int > deque_merge;
  std::deque< int > deque_qsort;
  std::list< int > bilist_standard;
  std::forward_list< int > forward_standard;
  std::deque< int > deque_standard;

  for (size_t i = 0; i < 10; ++i)
  {
    int num = dist(range);
    bilist_merge.pushBack(num);
    deque_merge.push_back(num);
    deque_qsort.push_back(num);
    bilist_standard.push_back(num);
    forward_standard.push_front(num);
    deque_standard.push_back(num);
  }

  merge_sort(bilist_merge.begin(), bilist_merge.end(), std::greater< int >());
  merge_sort(deque_merge.begin(), deque_merge.end(), std::greater< int >());
  quick_sort(deque_qsort.begin(), deque_qsort.end(), std::greater< int >());

  bilist_standard.sort(std::greater< int >());
  forward_standard.sort(std::greater< int >());

  std::sort(deque_standard.begin(), deque_standard.end(), std::greater< int >());

  for (auto value: bilist_merge)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";

  for (auto value: deque_merge)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";

  for (auto value: deque_qsort)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";

  for (auto value: bilist_standard)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";

  for (auto value: forward_standard)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";

  for (auto value: deque_standard)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";
}
