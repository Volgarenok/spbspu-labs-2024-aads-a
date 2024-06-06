#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
#include <ostream>
#include <functional>
#include <deque>
#include <list>
#include "generators.hpp"
#include "sorting_algorithms.hpp"

namespace detail
{
  template< typename Container >
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
  template< class Container, typename Comparator, typename InputIt, class Sort >
  void execute(std::ostream& out, InputIt begin, InputIt end, Sort sort)
  {
    Container container(begin, end);
    sort(container.begin(), container.end(), Comparator{});
    print(out, container);
  }
}
namespace zaitsev
{
  template< typename value_type, typename Compare >
  void check_sorts(std::ostream& out, size_t size)
  {
    std::vector< value_type > vals(size);
    generator< value_type > gen(0, 1000, 43);
    std::generate_n(vals.begin(), size, gen);
    detail::print(out, vals);
    using dq = std::deque < value_type >;
    using lst = std::list < value_type >;
    using Flist = zaitsev::ForwardList< value_type >;
    using namespace std::placeholders;
    auto binded_bucketsort = std::bind(&bucketSort< typename dq::iterator, Compare >, _1, _2, _3, 2);
    detail::execute< dq, Compare >(out, vals.cbegin(), vals.cend(), std::sort< typename dq::iterator, Compare >);
    detail::execute< dq, Compare >(out, vals.cbegin(), vals.cend(), shellSort< typename dq::iterator, Compare >);
    detail::execute< dq, Compare >(out, vals.cbegin(), vals.cend(), binded_bucketsort);
    detail::execute< lst, Compare >(out, vals.cbegin(), vals.cend(), shellSort< typename lst::iterator, Compare >);
    detail::execute< Flist, Compare >(out, vals.cbegin(), vals.cend(), shellSort< typename Flist::iterator, Compare >);
    Flist flist(vals.cbegin(), vals.cend());
    flist.sort(Compare{});
    detail::print(out, flist);
  }
}
#endif
