#ifndef SORT_FUNCTIONS_HPP
#define SORT_FUNCTIONS_HPP

#include <algorithm>
#include <iterator>

namespace erohin
{
  namespace detail
  {
    template< class ForwardIt, class Compare >
    ForwardIt doPartition(ForwardIt begin, ForwardIt end, Compare cmp)
    {
      auto pivot = begin;
      auto cur_iter = std::next(begin);
      while (cur_iter != end)
      {
        if (!cmp(*pivot, *cur_iter))
        {
          auto temp_iter = pivot;
          using T = typename ForwardIt::value_type;
          T temp(std::move(*cur_iter));
          while (temp_iter != std::next(cur_iter))
          {
            std::swap(*temp_iter, temp);
            ++temp_iter;
          }
          ++pivot;
        }
        ++cur_iter;
      }
      return pivot;
    }
  }

  template< class ForwardIt, class Compare >
  void doQuicksort(ForwardIt begin, ForwardIt end, Compare cmp)
  {
    if (begin != end)
    {
      auto pivot = detail::doPartition(begin, end, cmp);
      doQuicksort(begin, pivot, cmp);
      doQuicksort(std::next(pivot), end, cmp);
    }
  }

  namespace detail
  {
    template< class RandomAccessIt, class Compare >
    void doInsertsort(RandomAccessIt begin, size_t size, Compare cmp)
    {
      if (size <= 1)
      {
        return;
      }
      size_t i = 1;
      auto cur_iter = std::next(begin);
      while (i < size)
      {
        auto temp_iter = cur_iter;
        auto start = std::prev(cur_iter);
        while (temp_iter != begin)
        {
          if (cmp(*temp_iter, *start))
          {
            std::iter_swap(temp_iter, start);
            --temp_iter;
          }
          else
          {
            break;
          }
          start--;
        }
        ++cur_iter;
        ++i;
      }
    }

    template< class RandomAccessIt, class Compare >
    void doMergesort(RandomAccessIt begin, size_t size, Compare cmp)
    {
      if (size <= 1)
      {
        return;
      }
      size_t left_size = size / 2;
      size_t right_size = size - size / 2;
      doMergesort(begin, left_size, cmp);
      doMergesort(begin + left_size, right_size, cmp);
      size_t l_size = left_size;
      size_t r_size = right_size;
      using T = typename RandomAccessIt::value_type;
      T * temp_arr = new T[size]{ *begin };
      try
      {
        while ((l_size > 0) || (r_size > 0))
        {
          size_t cur_index = size - l_size - r_size;
          if (r_size == 0 || (l_size > 0 && cmp(begin[left_size - l_size], begin[left_size + right_size - r_size])))
          {
            temp_arr[cur_index] = std::move(begin[left_size - l_size]);
            --l_size;
          }
          else
          {
            temp_arr[cur_index] = std::move(begin[left_size + right_size - r_size]);
            --r_size;
          }
        }
        for (size_t i = 0; i < size; ++i)
        {
          begin[i] = std::move(temp_arr[i]);
        }
        delete[] temp_arr;
      }
      catch (...)
      {
        delete[] temp_arr;
        throw;
      }

    }
  }

  template< class RandomAccessIt, class Compare >
  void doTimsort(RandomAccessIt begin, size_t size, Compare cmp)
  {
    if (size <= 1)
    {
      return;
    }
    size_t min_run = 0;
    size_t n = size;
    while (n >= 64)
    {
      min_run |= n & 1;
      n = n >> 1;
    }
    min_run = n + min_run;
    for (size_t i = 0; i < size; i += min_run)
    {
      detail::doInsertsort(begin + i, min_run, cmp);
    }
    size_t run = min_run;
    while (run < size)
    {
      for (size_t i = 0; i < size; i += (run * 2))
      {
        detail::doMergesort(begin + i, run * 2, cmp);
      }
      run *= 2;
    }
  }
}

#endif
