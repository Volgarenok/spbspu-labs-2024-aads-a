#ifndef SORTINGSHEETS_HPP
#define SORTINGSHEETS_HPP
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <list>
#include <iostream>
#include <string>
#include <list.hpp>
#include "generate.hpp"
#include "sorting.hpp"
#include "print.hpp"

template< class Type >
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
    else
    {
      throw std::logic_error ("Bad type");
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
    prType(std::cout, forwardList);

    auto beginBiR = biListRealization.begin();
    auto beginDeqSort = dequeSort.begin();
    auto endDeqSort = dequeSort.end();
    auto beginDeqShaker = dequeShaker.begin();
    auto beginDeqShell = dequeShell.begin();

    shaker(++beginBiR, size, std::less< Type >());
    biListStandart.sort(std::less< Type >());
    std::sort(beginDeqSort, endDeqSort, std::less< Type >());
    shaker(++beginDeqShaker, size, std::less< Type >());
    shell(beginDeqShell, size, std::less< Type >());
    forwardList.sort(std::less< Type >());

    prType(std::cout, biListRealization);
    prType(std::cout, biListStandart);
    prType(std::cout, dequeSort);
    prType(std::cout, dequeShaker);
    prType(std::cout, dequeShell);
    prType(std::cout, forwardList);
}

#endif
