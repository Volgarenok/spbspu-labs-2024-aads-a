#ifndef DO_CMD_HPP
#define DO_CMD_HPP

#include <ostream>
#include <algorithm>
#include <list/list.hpp>
#include <deque>
#include <list>
#include <forward_list>

namespace isaychev
{
  template < class T, class Cmp >
  void do_cmd(std::ostream & out, size_t seq_size)
  {
    List< T > src;
    for (size_t i = 0; i < seq_size; ++i)
    {
      //src.push_front(generate_rand());
    }
    /*List< T > fwd;
    for (auto i = src.cbegin(); i != src.cend(); ++i)
    {
      fwd.push_front(*i);
    }*/
    std::forward_list< T > fwd_std(src.cbegin(), src.cend());
    std::list< T > bi_std(src.cbegin(), src.cend());
    std::deque< T > deq_std(src.cbegin(), src.cend());

    fwd_std.sort(Cmp());
    bi_std.sort(Cmp());
    std::sort(deq_std.begin(), deq_std.end(), Cmp());
  }
}

#endif
