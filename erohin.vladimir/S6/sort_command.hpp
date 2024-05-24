#ifndef SORT_COMMAND
#define SORT_COMMAND

#include <iostream>
#include <functional>
#include <list>
#include <deque>
#include "dynamic_array.hpp"
#include "list.hpp"
#include "sequence_operations.hpp"
#include "sort_functions.hpp"

namespace erohin
{
  template< class T, class Compare >
  void doSortCommand(std::ostream & output, size_t size)
  {
    Compare cmp;
    DynamicArray< T > random_seq(size);
    std::generate(random_seq.begin(), random_seq.end(), std::bind(getRandom< T >, -1000, 1000));
    List< T > first_forward_list(random_seq.cbegin(), random_seq.cend());
    std::list< T > first_bi_list(random_seq.cbegin(), random_seq.cend());
    std::list< T > second_bi_list(random_seq.cbegin(), random_seq.cend());
    std::deque< T > first_deque(random_seq.cbegin(), random_seq.cend());
    std::deque< T > second_deque(random_seq.cbegin(), random_seq.cend());
    std::deque< T > third_deque(random_seq.cbegin(), random_seq.cend());
    doQuicksort(first_forward_list.begin(), first_forward_list.end(), cmp);
    doQuicksort(first_bi_list.begin(), first_bi_list.end(), cmp);
    second_bi_list.sort(cmp);
    doQuicksort(first_deque.begin(), first_deque.end(), cmp);
    doTimsort(second_deque.begin(), size, cmp);
    std::sort(third_deque.begin(), third_deque.end(), cmp);
    printSequence(output, random_seq.cbegin(), random_seq.cend());
    printSequence(output << "\n", first_forward_list.cbegin(), first_forward_list.cend());
    printSequence(output << "\n", first_bi_list.cbegin(), first_bi_list.cend());
    printSequence(output << "\n", second_bi_list.cbegin(), second_bi_list.cend());
    printSequence(output << "\n", first_deque.cbegin(), first_deque.cend());
    printSequence(output << "\n", second_deque.cbegin(), second_deque.cend());
    printSequence(output << "\n", third_deque.cbegin(), third_deque.cend());
    output << "\n";
  }
}

#endif
