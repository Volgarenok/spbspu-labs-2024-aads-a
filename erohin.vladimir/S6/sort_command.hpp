#ifndef SORT_COMMAND
#define SORT_COMMAND

#include <iostream>
#include <list>
#include <deque>
#include <forward_list>
#include <functional>
#include "list.hpp"
#include "sequence_operations.hpp"
#include "sort_functions.hpp"

namespace erohin
{
  template< class T, class Compare >
  void doSortCommand(std::ostream & output, size_t n, Compare)
  {
    std::forward_list< T > random_seq;
    generateRandomSequence< T >(random_seq, n);
    std::forward_list< T > forward_list_seq[2];
    std::list< T > bidirect_list_seq[2];
    std::deque< T > deque_seq[2];
    for (int i = 0; i < 2; ++i)
    {
      forward_list_seq[i].assign(random_seq.cbegin(), random_seq.cend());
      bidirect_list_seq[i].assign(random_seq.cbegin(), random_seq.cend());
      deque_seq[i].assign(random_seq.cbegin(), random_seq.cend());
    }
    //sort1(forward_list_seq[0].begin(), forward_list_seq[0].end(), cmp);
    //sort2(forward_list_seq[1].begin(), forward_list_seq[1].end(), cmp);
    //sort1(bidirect_list_seq[0].begin(), bidirect_list_seq[0].end(), cmp);
    //sort2(bidirect_list_seq[1].begin(), bidirect_list_seq[1].end(), cmp);
    //sort1(deque_seq[0].begin(), deque_seq[0].end(), cmp);
    //sort2(deque_seq[1].begin(), deque_seq[1].end(), cmp);
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
