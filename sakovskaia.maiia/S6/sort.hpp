#ifndef SORT_HPP
#define SORT_HPP
#include <string>
#include <list>
#include <deque>
#include <vector>
#include "list.hpp"
#include "input_output.hpp"

namespace sakovskaia
{
  template <typename ForwardIt, typename Compare>
  void bucketSort(ForwardIt first, ForwardIt last, Compare comp)
  {
    if (first == last)
    {
      return;
    }
    auto min_elem = * first;
    auto max_elem = * first;
    for (auto it = first; it != last; ++it)
    {
      if (comp(* it, min_elem))
      {
        min_elem = * it;
      }
      if (comp(max_elem, * it) == false)
      {
        max_elem = * it;
      }
    }
    size_t num_buckets = 2;
    auto range = max_elem - min_elem + 1;
    auto bucket_size = static_cast< double >(range) / num_buckets;
    std::vector< std::list< typename ForwardIt::value_type > > buckets(num_buckets);
    for (auto it = first; it != last; ++it)
    {
      size_t bucket_index = static_cast< size_t >((* it - min_elem) / bucket_size);
      if (bucket_index >= num_buckets)
      {
        bucket_index = num_buckets - 1;
      }
      buckets[bucket_index].push_back(* it);
    }
    for (auto bucket_it = buckets.begin(); bucket_it != buckets.end(); ++bucket_it)
    {
      auto & bucket = * bucket_it;
      bucket.sort(comp);
    }
  }
}

#endif

