#ifndef TEST_SORTINGS_HPP
#define TEST_SORTINGS_HPP

#include <ostream>
#include <cstddef>
#include <vector>
#include <list>
#include <deque>
#include <functional>
#include <random>
#include <forward_list.hpp>
#include "shell_sort.hpp"
#include "selection_sort.hpp"

namespace namestnikov
{
  namespace detail
  {
    template< class Iter >
    void printData(Iter first, Iter last, std::ostream & out)
    {
      auto temp = first;
      ++temp;
      for (; temp != last; ++temp)
      {
        out << *first << " ";
        ++first;
      }
      out << *first << "\n";
    }
    template< class T >
    T getNumber(std::default_random_engine & generator)
    {
      std::uniform_real_distribution< float > dist(-1000, 1000);
      return static_cast< T >(dist(generator));
    }
  }
}

namespace namestnikov
{
  template< class T, class Compare >
  void testSortings(std::ostream & out, std::default_random_engine & generator, size_t size)
  {
    std::vector< T > data(size);
    std::generate(data.begin(), data.end(), std::bind(detail::getNumber< T >, generator));
    detail::printData(data.begin(), data.end(), out);
    Compare compare;
    ForwardList< T > forwardlistSelection(data.begin(), data.end());
    std::list< T > listSelection(data.begin(), data.end());
    std::list< T > listShell(data.begin(), data.end());
    std::deque< T > dequeSelection(data.begin(), data.end());
    std::deque< T > dequeShell(data.begin(), data.end());
    std::deque< T > dequeNormal(data.begin(), data.end());
    doSelectionSort(forwardlistSelection.begin(), size, compare);
    doSelectionSort(listSelection.begin(), size, compare);
    doShellSort(listShell.begin(), size, compare);
    doSelectionSort(dequeSelection.begin(), size, compare);
    doShellSort(dequeShell.begin(), size, compare);
    std::sort(dequeNormal.begin(), dequeNormal.end(), compare);
    detail::printData(forwardlistSelection.begin(), forwardlistSelection.end(), out);
    detail::printData(listSelection.begin(), listSelection.end(), out);
    detail::printData(listShell.begin(), listShell.end(), out);
    detail::printData(dequeSelection.begin(), dequeSelection.end(), out);
    detail::printData(dequeShell.begin(), dequeShell.end(), out);
    detail::printData(dequeNormal.begin(), dequeNormal.end(), out);
  }
}

#endif
