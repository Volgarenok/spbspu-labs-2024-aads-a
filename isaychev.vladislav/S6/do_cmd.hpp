#ifndef DO_CMD_HPP
#define DO_CMD_HPP

#include <algorithm>
#include <list/list.hpp>
#include <deque>
#include <list>
#include <random>
#include <forward_list>
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
    /*List< T > fwd;
    for (auto i = src.cbegin(); i != src.cend(); ++i)
    {
      fwd.push_front(*i);
    }*/
    std::forward_list< T > fwd_std(src.cbegin(), src.cend());
    std::list< T > bi_std(src.cbegin(), src.cend());
    std::deque< T > deq_std(src.cbegin(), src.cend());

    detail::do_sort(out, deq_std.begin(), deq_std.end(), Cmp(), std::sort);

    fwd_std.sort(Cmp());
    output_range(out, fwd_std.cbegin(), fwd_std.cend());
    bi_std.sort(Cmp());
    output_range(out, bi_std.cbegin(), bi_std.cend());
    //std::sort(deq_std.begin(), deq_std.end(), Cmp());
    //output_range(out, deq_std.cbegin(), deq_std.cend());
  }

}

#endif
