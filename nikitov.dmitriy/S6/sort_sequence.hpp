#ifndef SORT_SEQUENCE_HPP
#define SORT_SEQUENCE_HPP

#include <deque>
#include <forward_list>
#include <algorithm>
#include <iomanip>
#include <list.hpp>
#include <tree.hpp>
#include "sortings.hpp"
#include "iterators_functions.hpp"

namespace nikitov
{
  namespace detail
  {
    int generateValue(int);
    float generateValue(float);

    template< class T, class Compare, class Container >
    void createAndSort(const std::forward_list< T >& list, void(*sort)(typename Container::iterator, typename Container::iterator, Compare), 
      std::ostream& output)
    {
      Container type;
      for (auto i = list.cbegin(); i != list.cend(); ++i)
      {
        type.push_front(*i);
      }
      sort(type.begin(), type.end(), Compare());
      printRange(type.cbegin(), type.cend(), output);
    }

    template< class T, class Compare, class Container >
    void createAndSortByMethod(const std::forward_list< T >& list, std::ostream& output)
    {
      Container type;
      for (auto i = list.cbegin(); i != list.cend(); ++i)
      {
        type.push_front(*i);
      }
      type.sort();
      printRange(type.cbegin(), type.cend(), output);
    } 
  }

  template< class T, class Compare >
  void sortSequence(size_t size, std::ostream& output)
  {
    std::forward_list< T > values;
    for (size_t i = 0; i != size; ++i)
    {
      T value = generateValue(T());
      values.push_front(value);
    }

    output << std::setprecision(1) << std::fixed;
    printRange(values.cbegin(), values.cend(), output);

    detail::createAndSortByMethod< T, Compare, std::forward_list< T > >(values, output);
    detail::createAndSortByMethod< T, Compare, List< T > >(values, output);
    detail::createAndSort< T, Compare, List< T > >(values, oddEvenSort, output);
    detail::createAndSort< T, Compare, std::deque< T > >(values, oddEvenSort, output);
    detail::createAndSort< T, Compare, std::deque< T > >(values, QSort, output);
    detail::createAndSort< T, Compare, std::deque< T > >(values, std::sort, output);
  }
}
#endif
