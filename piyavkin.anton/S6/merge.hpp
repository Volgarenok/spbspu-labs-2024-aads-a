#ifndef MERGE_HPP
#define MERGE_HPP
#include <list.hpp>

namespace piyavkin
{
  template< class BiIter, class Cmp >
  void merge(BiIter first, BiIter second, BiIter end, Cmp cmp, List< typename BiIter::val_t >& res)
  {
    BiIter border = second;
    while (first != border || second != end)
    {
      if (second == end || (first != border && cmp(*first, *second)))
      {
        res.push_back(*first++);
      }
      else
      {
        res.push_back(*second++);
      }
    }
  }
  template< class BiIter, class Cmp >
  void sort_merge(BiIter begin, BiIter end, Cmp cmp)
  {
  }
}
#endif