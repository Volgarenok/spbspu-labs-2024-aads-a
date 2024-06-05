#ifndef SORTPROCESSING_HPP
#define SORTPROCESSING_HPP

#include <iostream>
#include <list>
#include <deque>
#include <random>

#include <list.hpp>

#include "sorts.hpp"

namespace gladyshev
{
  template < typename Container >
  void printContainer(const Container& container, std::ostream& out)
  {
    auto it = container.cbegin();
    out << *it;
    for (auto it = ++container.cbegin(); it != container.cend(); ++it)
    {
      out << " " << *it;
    }
    out << "\n";
  }
  template < typename T, typename Compare >
  void processSorts(size_t size, std::ostream& out)
  {
    std::deque< T > deq;
    List< T > selecList;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1000.0, 1000.0);
    for (size_t i = 0; i < size; ++i)
    {
      auto temp = static_cast< T >(dis(gen));
      deq.push_back(temp);
      selecList.push_front(temp);
    }
    std::list< T > selecBiList(deq.cbegin(), deq.cend());
    std::list< T > mergeBiList(deq.cbegin(), deq.cend());
    std::deque< T > sortDec(deq.cbegin(), deq.cend());
    std::deque< T > selecDec(deq.cbegin(), deq.cend());
    std::deque< T > mergeDec(deq.cbegin(), deq.cend());
    selection(selecBiList.begin(), selecBiList.end(), Compare());
    merge(mergeBiList.begin(), mergeBiList.end(), Compare());
    std::sort(sortDec.begin(), sortDec.end(), Compare());
    selection(selecDec.begin(), selecDec.end(), Compare());
    merge(mergeDec.begin(), mergeDec.end(), Compare());
    selection(selecList.begin(), selecList.end(), Compare());
    printContainer(deq, out);
    printContainer(selecList, out);
    printContainer(selecBiList, out);
    printContainer(selecDec, out);
    printContainer(sortDec, out);
    printContainer(mergeDec, out);
    printContainer(mergeBiList, out);
  }
}

#endif
