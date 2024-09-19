#ifndef DO_CMD_HPP
#define DO_CMD_HPP

#include <algorithm>
#include <list/list.hpp>
#include <deque>
#include <list>
#include <random>
#include <forward_list>
#include <sorts.hpp>
#include "output_range.hpp"

namespace isaychev
{
  namespace detail
  {
    template < class Iter, class Cmp >
    void do_sort(std::ostream & out, Iter first, Iter last, Cmp cmp, void (*sort)(Iter, Iter, Cmp))
    {
      sort(first, last, cmp);
      output_range(out, first, last);
      out << "\n";
    }

    template < class Iter, class Cmp >
    void do_sort(std::ostream & out, Iter first, Iter last, size_t size, Cmp cmp, void (*sort)(Iter, size_t, Cmp))
    {
      sort(first, size, cmp);
      output_range(out, first, last);
      out << "\n";
    }
  }

  template < class T, class Cmp >
  void do_cmd(std::ostream & out, size_t seq_size)
  {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution< int > dist(-1000, 1000);
    List< T > src;
    for (size_t i = 0; i < seq_size; ++i)
    {
      src.push_front(dist(gen));
    }
    output_range(out, src.begin(), src.end());
    out << "\n";

    List< T > fwd;
    for (auto i = src.begin(); i != src.end(); ++i)
    {
      fwd.push_front(*i);
    }
    std::list< T > bi_qsort(src.begin(), src.end());
    std::deque< T > deq_qsort(src.begin(), src.end());
    std::deque< T > deq_merge(src.begin(), src.end());
    std::forward_list< T > fwd_std(src.begin(), src.end());
    std::deque< T > deq_std(src.begin(), src.end());

    detail::do_sort(out, fwd.begin(), fwd.end(), Cmp(), quick_sort);
    detail::do_sort(out, bi_qsort.begin(), bi_qsort.end(), Cmp(), quick_sort);
    detail::do_sort(out, deq_qsort.begin(), deq_qsort.end(), Cmp(), quick_sort);
    detail::do_sort(out, deq_merge.begin(), deq_merge.end(), seq_size, Cmp(), merge_sort);
    fwd_std.sort(Cmp());
    output_range(out, fwd_std.cbegin(), fwd_std.cend());
    out << "\n";
    detail::do_sort(out, deq_std.begin(), deq_std.end(), Cmp(), std::sort);
  }
}

#endif
