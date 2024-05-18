#ifndef SORTINGSHEETS_HPP
#define SORTINGSHEETS_HPP
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <string>
#include <list.hpp>
#include "generate.hpp"
#include "print.hpp"
#include "sorting.hpp"

namespace zakozhurnikova
{
  template < class Type >
  void sortingSheets(std::string sort, std::string kind, size_t size)
  {
    Type array[10000];
    if (kind == "ints")
    {
      std::generate_n(array, size, RandomNumberInt);
    }
    else if (kind == "floats")
    {
      std::generate_n(array, size, RandomNumberFloat);
    }
    List< Type > biListRealization;
    std::list< Type > biListStandart;
    std::deque< Type > dequeSort;
    std::deque< Type > dequeShaker;
    std::deque< Type > dequeShell;
    std::forward_list< Type > forwardList;

    for (size_t i = 0; i < size; ++i)
    {
      Type number = array[i];
      biListRealization.push_back(number);
      biListStandart.push_front(number);
      dequeSort.push_front(number);
      dequeShaker.push_front(number);
      dequeShell.push_front(number);
      forwardList.push_front(number);
    }
    print(std::cout, forwardList);

    auto beginBiR = biListRealization.begin();
    auto beginDeqSort = dequeSort.begin();
    auto endDeqSort = dequeSort.end();
    auto beginDeqShaker = dequeShaker.begin();
    auto beginDeqShell = dequeShell.begin();

    if (sort == "ascending")
    {
      shaker(++beginBiR, size, std::less< Type >());
      biListStandart.sort(std::less< Type >());
      std::sort(beginDeqSort, endDeqSort, std::less< Type >());
      shaker(++beginDeqShaker, size, std::less< Type >());
      shell(beginDeqShell, size, std::less< Type >());
      forwardList.sort(std::less< Type >());
    }
    else if (sort == "descending")
    {
      shaker(++beginBiR, size, std::greater< Type >());
      biListStandart.sort(std::greater< Type >());
      std::sort(beginDeqSort, endDeqSort, std::greater< Type >());
      shaker(++beginDeqShaker, size, std::greater< Type >());
      shell(beginDeqShell, size, std::greater< Type >());
      forwardList.sort(std::greater< Type >());
    }
    else
    {
      throw std::logic_error("Bad sort");
    }
    print(std::cout, biListRealization);
    print(std::cout, biListStandart);
    print(std::cout, dequeSort);
    print(std::cout, dequeShaker);
    print(std::cout, dequeShell);
    print(std::cout, forwardList);
  }
}
#endif
