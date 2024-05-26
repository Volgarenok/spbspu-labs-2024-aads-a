#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
#include <ostream>
#include <deque>
#include <list>
#include <algorithm>
#include <forward_list.hpp>
#include "generators.hpp"
#include "sorting_algorithms.hpp"

namespace detail
{
  template< typename Container, typename value_type = typename Container::const_iterator::value_type >
  void print(std::ostream& out, const Container& container)
  {
    typename Container::const_iterator it = container.cbegin();
    out << *it;
    for (++it; it != container.cend(); ++it)
    {
      out << ' ' << *it;
    }
    out << '\n';
  }
  template< class Container, typename Comparator, typename InputIt, class Iter = typename Container::iterator >
  void execute(std::ostream& out, InputIt begin, InputIt end, void (*sort)(Iter, Iter, Comparator))
  {
    Container container(begin, end);
    sort(container.begin(), container.end(), Comparator{});
    print(out, container);
  }
}
namespace zaitsev
{
  template< typename value_type, typename Compare >
  void sortirator(std::ostream& out, size_t size)
  {
    using namespace detail;
    std::vector< value_type > vals(size);
    generator< value_type > gen(0, 1000, 43);
    std::generate_n(vals.begin(), size, gen);
    print(out, vals);
    using dq = std::deque < value_type >;
    using lst = std::list < value_type >;
    using Flist = zaitsev::ForwardList< value_type >;
    execute< dq, Compare >(out, vals.cbegin(), vals.cend(), std::sort< typename dq::iterator, Compare >);
    execute< dq, Compare >(out, vals.cbegin(), vals.cend(), shellSort< typename dq::iterator, Compare >);
    execute< dq, Compare >(out, vals.cbegin(), vals.cend(), shellSort< typename dq::iterator, Compare >);
    execute< lst, Compare >(out, vals.cbegin(), vals.cend(), shellSort< typename lst::iterator, Compare >);
    execute< Flist, Compare >(out, vals.cbegin(), vals.cend(), shellSort< typename Flist::iterator, Compare >);
    Flist flist(vals.cbegin(), vals.cend());
    flist.sort(Compare{});
    detail::print(out, flist);
  }
}
#endif
