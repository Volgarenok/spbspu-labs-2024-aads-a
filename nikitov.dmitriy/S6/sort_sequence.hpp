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
    template< class T >
    T generateValue()
    {
      return static_cast< T > (std::rand());
    }

    template< class T, class Compare, class Container >
    void createAndSort(const std::deque< T >& sequence, void(*sort)(typename Container::iterator, typename Container::iterator, Compare),
      std::ostream& output)
    {
      Container type;
      for (auto i = sequence.cbegin(); i != sequence.cend(); ++i)
      {
        type.push_front(*i);
      }
      sort(type.begin(), type.end(), Compare());
      printRange(type.cbegin(), type.cend(), output);
    }

    template< class T, class Compare, class Container >
    void createAndSortByMethod(const std::deque< T >& sequence, std::ostream& output)
    {
      Container type;
      for (auto i = sequence.cbegin(); i != sequence.cend(); ++i)
      {
        type.push_front(*i);
      }
      type.sort(Compare());
      printRange(type.cbegin(), type.cend(), output);
    }
  }

  template< class T, class Compare >
  void sortSequence(size_t size, std::ostream& output)
  {
    std::deque< T > sequence;
    std::generate_n(std::back_inserter(sequence), size, nikitov::detail::generateValue< T >);

    output << std::setprecision(1) << std::fixed;
    printRange(sequence.cbegin(), sequence.cend(), output);

    detail::createAndSortByMethod< T, Compare, std::forward_list< T > >(sequence, output);
    detail::createAndSortByMethod< T, Compare, List< T > >(sequence, output);
    detail::createAndSort< T, Compare, List< T > >(sequence, oddEvenSort, output);
    detail::createAndSort< T, Compare, std::deque< T > >(sequence, oddEvenSort, output);
    detail::createAndSort< T, Compare, std::deque< T > >(sequence, QSort, output);
    detail::createAndSort< T, Compare, std::deque< T > >(sequence, std::sort, output);
  }
}
#endif
