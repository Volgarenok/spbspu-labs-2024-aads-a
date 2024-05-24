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
  template < class Type, class Compare >
  void sortAndPrint(const std::string& kind, size_t size, Compare cmp)
  {
    Type array[10000];
    if (kind == "ints")
    {
      std::generate_n(array, size, detail::randomNumberInt);
    }
    else if (kind == "floats")
    {
      std::generate_n(array, size, detail::randomNumberFloat);
    }
    List< Type > biListRealization(array, array + size);
    std::list< Type > biListStandart(array, array + size);
    std::deque< Type > dequeSort(array, array + size);
    std::deque< Type > dequeShaker(array, array + size);
    std::deque< Type > dequeShell(array, array + size);
    std::forward_list< Type > forwardList(array, array + size);

    print(std::cout, forwardList);
    std::cout << '\n';

    auto beginBiR = biListRealization.begin();
    auto beginDeqSort = dequeSort.begin();
    auto endDeqSort = dequeSort.end();
    auto beginDeqShaker = dequeShaker.begin();
    auto beginDeqShell = dequeShell.begin();

    shaker(beginBiR, size, cmp);
    biListStandart.sort(cmp);
    std::sort(beginDeqSort, endDeqSort, cmp);
    shaker(beginDeqShaker, size, cmp);
    shell(beginDeqShell, size, cmp);
    forwardList.sort(cmp);

    print(std::cout, biListRealization);
    std::cout << '\n';
    print(std::cout, biListStandart);
    std::cout << '\n';
    print(std::cout, dequeSort);
    std::cout << '\n';
    print(std::cout, dequeShaker);
    std::cout << '\n';
    print(std::cout, dequeShell);
    std::cout << '\n';
    print(std::cout, forwardList);
    std::cout << '\n';
  }

}
#endif
