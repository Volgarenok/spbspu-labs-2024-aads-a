#ifndef SORT_COMMAND
#define SORT_COMMAND

#include <iostream>
#include <functional>
#include <list>
#include <deque>
#include "list.hpp"
#include "sequence_operations.hpp"
#include "sort_functions.hpp"

namespace erohin
{
  template< class T, class Compare >
  void doSortCommand(std::ostream & output, size_t n)
  {
    Compare cmp;
    List< T > random_seq;
    generateRandomSequence< T >(random_seq, n);
    List< T > forward_list_seq[2];
    std::list< T > bidirect_list_seq[2];
    std::deque< T > deque_seq[2];
    for (int i = 0; i < 2; ++i)
    {
      forward_list_seq[i].assign(random_seq.cbegin(), random_seq.cend());
      bidirect_list_seq[i].assign(random_seq.cbegin(), random_seq.cend());
      deque_seq[i].assign(random_seq.cbegin(), random_seq.cend());
    }
    forward_list_seq[0].sort(cmp);
    forward_list_seq[1].sort(cmp);
    bidirect_list_seq[0].sort(cmp);
    bidirect_list_seq[1].sort(cmp);
    sort1(deque_seq[0].begin(), deque_seq[0].end(), cmp);
    //sort2(deque_seq[1].begin(), deque_seq[1].end(), cmp);

    doQuickSort(deque_seq[1].begin(), std::prev(deque_seq[1].end()), cmp);

    printSequence(output, random_seq.begin(), random_seq.end());
    for (int i = 0; i < 2; ++i)
    {
      printSequence(output << "\n", forward_list_seq[i].cbegin(), forward_list_seq[i].cend());
      printSequence(output << "\n", bidirect_list_seq[i].cbegin(), bidirect_list_seq[i].cend());
      printSequence(output << "\n", deque_seq[i].cbegin(), deque_seq[i].cend());
    }
    output << "\n";
  }
}

#endif
