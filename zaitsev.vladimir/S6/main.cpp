#include <algorithm>
#include <iostream>
#include <iterator>
#include <forward_list.hpp>
#include <vector>
#include <functional>
#include <deque>
#include <map>
#include <list>
#include <string>
#include "generators.hpp"

template< class ForwardIt, class Comapare >
void shellSort(ForwardIt begin, ForwardIt end, Comapare cmp, size_t size = 0)
{
  if (size == 0)
  {
    ForwardIt copy = begin;
    while (copy != end)
    {
      ++size;
      ++copy;
    }
  }
  size_t diff = size;
  while (diff > 1)
  {
    diff /= 2;
    ForwardIt front_start = begin;
    std::advance(front_start, diff);
    size_t swaps = 1;
    while (swaps != 0)
    {
      ForwardIt front = front_start;
      ForwardIt back = begin;
      swaps = 0;
      while (front != end)
      {
        if (cmp(*front, *back))
        {
          std::swap(*back, *front);
          ++swaps;
        }
        ++front;
        ++back;
      }
    }
  }
}

template< class ForwardIt, class Comapare >
void bucketSort(ForwardIt begin, ForwardIt end, Comapare cmp, size_t buckets_nmb = 10)
{
  using T = typename ForwardIt::value_type;
  if (begin == end)
  {
    return;
  }
  size_t size = 1;
  T max_val = *begin;
  T min_val = *begin;
  bool is_sorted = false;
  ForwardIt cur = begin;
  ForwardIt pre_cur = begin;
  ++cur;
  while (cur != end)
  {
    min_val = cmp(*cur, min_val) ? *cur : min_val;
    max_val = cmp(max_val, *cur) ? *cur : max_val;
    is_sorted |= !cmp(*cur, *pre_cur);
    ++size;
    ++cur;
    ++pre_cur;
  }


}

template< typename value_type, typename comparator >
void sortirator(size_t size)
{
  using namespace zaitsev;
  using std::deque;
  using std::list;
  comparator cmp();
  generator< value_type > gen(0, 1000);
  deque< value_type > deque_sort;
  generate_n(std::back_inserter(deque_inbuild), size, gen);
  std::copy(deque_sort.begin(), deque_sort.end(), std::ostream_iterator< value_type >(std::cout, " "));
  std::cout << '\n';

  deque< value_type > deque_shell(deque_inbuild.cbegin(), deque_inbuild.cend());
  //  deque< value_type > deque_bucket(deque_inbuild.cbegin(),deque_inbuild.cend());;

  ForwardList< value_type > forward_inbuild(deque_inbuild.cbegin(),deque_inbuild.cend());
  ForwardList< value_type > forward_shell(deque_inbuild.cbegin(), deque_inbuild.cend());
  list< value_type > list_shell(deque_inbuild.cbegin(), deque_inbuild.cend());
  list< value_type > list_inbuild(deque_inbuild.cbegin(), deque_inbuild.cend());

  std::sort(deque_sort.begin(), deque_sort.end(), cmp);
  shellSort(deque_sort.begin(), deque_sort.end(), cmp);
//  bucketSort(deque_sort.begin(), deque_sort.end(), cmp);

  forward_inbuild.sort(cmp);
  shell(forward_inbuild.begin(), forward_inbuild.end(), cmp);

  list_inbuild.sort(cmp);
  shellSort(list_shell.begin(), list_shell.end(), cmp);

  std::copy(deque_sort.begin(), deque_sort.end(), std::ostream_iterator< value_type >(std::cout, " "));
  std::cout << '\n';
  std::copy(deque_shell.begin(), deque_shell.end(), std::ostream_iterator< value_type >(std::cout, " "));
  std::cout << '\n';
  std::copy(lst1.begin(), lst1.end(), std::ostream_iterator< value_type >(std::cout, " "));
  std::cout << '\n';
  std::copy(lst2.begin(), lst2.end(), std::ostream_iterator< value_type >(std::cout, " "));
  std::cout << '\n';
  std::copy(lst3.begin(), lst3.end(), std::ostream_iterator< value_type >(std::cout, " "));
  std::copy(deque_sort.begin(), deque_sort.end(), std::ostream_iterator< value_type >(std::cout, " "));
  std::cout << '\n';
}

int main(int argc, char** argv)
{
  std::map< std::pair< std::string, std::string >, std::function< void(size_t) > >s;
  s[std::make_pair("ints", "ascending")] = sortirator< int, std::less< int > >;
  s[std::make_pair("ints", "descending]")] = sortirator< int, std::greater< int > >;
  s[std::make_pair("floats", "ascending")] = sortirator< float, std::less< float > >;
  s[std::make_pair("floats", "descending")] = sortirator< float, std::greater< float > >;
  constexpr size_t size = 10;
  using namespace zaitsev;
  float v[size];
  generator<float> gen(0, 1000);
  std::generate_n(v, size, gen);
  ForwardList< float > lst1(v, v + size);
  ForwardList< float > lst2(v, v + size);
  std::deque< float > lst3(v, v + size);
  std::copy(lst1.begin(), lst1.end(), std::ostream_iterator< float >(std::cout, " "));
  std::cout << '\n';
  shellSort(lst1.begin(), lst1.end(), std::less< float >{});
  shellSort(lst3.begin(), lst3.end(), std::less< float >{});
  lst2.sort(std::less< float >{});
  std::copy(lst1.begin(), lst1.end(), std::ostream_iterator< float >(std::cout, " "));
  std::cout << '\n';
  std::copy(lst2.begin(), lst2.end(), std::ostream_iterator< float >(std::cout, " "));
  std::cout << '\n';
  std::copy(lst3.begin(), lst3.end(), std::ostream_iterator< float >(std::cout, " "));
  return 0;
}
