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
  template < typename ForwardIt, typename Compare >
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

  template < typename RandomIt, typename Compare >
  void shellSort(RandomIt first, RandomIt last, Compare comp)
  {
    auto n = std::distance(first, last);
    for (auto gap = n / 2; gap > 0; gap /= 2)
    {
      for (auto i = first; std::distance(first, i) < n; ++i)
      {
        auto tempIt = i;
        for (auto j = tempIt; std::distance(first, j) >= gap; std::advance(j, -gap))
        {
          auto prevGapIt = j;
          std::advance(prevGapIt, -gap);
          if (comp(* tempIt, * prevGapIt))
          {
            std::swap(* tempIt, * prevGapIt);
            tempIt = prevGapIt;
          }
          else
          {
            break;
          }
        }
      }
    }
  }

  template < typename T >
  void sorting(const std::string & type, std::deque< T > & deque, List< T > & fwdList, std::list< T > & biList, std::ostream & output)
  {
    std::list< T > seconsBiList = biList;
    std::deque< T > scondDeque = deque;
    std::deque< T > thirdDeque = deque;
    if (type == "ascending")
    {
      bucketSort(fwdList.begin(), fwdList.end(), std::less< T >());
      shellSort(biList.begin(), biList.end(), std::less< T >());
      seconsBiList.sort(std::less< T >());
      bucketSort(deque.begin(), deque.end(), std::less< T >());
      shellSort(scondDeque.begin(), scondDeque.end(), std::less< T >());
      std::sort(thirdDeque.begin(), thirdDeque.end(), std::less< T >());
    }
    else if (type == "descending")
    {
      bucketSort(fwdList.begin(), fwdList.end(), std::greater< T >());
      shellSort(biList.begin(), biList.end(), std::greater< T >());
      seconsBiList.sort(std::greater< T >());
      bucketSort(deque.begin(), deque.end(), std::greater< T >());
      shellSort(scondDeque.begin(), scondDeque.end(), std::greater< T >());
      std::sort(thirdDeque.begin(), thirdDeque.end(), std::greater< T >());
    }
    else
    {
      throw std::invalid_argument("Error type of sort");
    }
    print(output, fwdList);
    print(output, biList);
    print(output, seconsBiList);
    print(output, deque);
    print(output, scondDeque);
    print(output, thirdDeque);
  }
}

#endif

