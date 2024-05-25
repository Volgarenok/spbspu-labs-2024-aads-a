#include <algorithm>
#include <iostream>

template< class Iter, class Compare >
void doShellSort(Iter begin, size_t size, Compare compare)
{
  for (size_t gap = size / 2, gap > 0; gap /= 2)
  {
    for (size_t i = gap, i < size; ++i)
    {
      auto temp = *std::advance(begin, i);
      for (size_t j = i; ((j >= gap) && (compare(temp, *std::advance(begin, j - gap)))); j -= gap)
      {
        *std::advance(begin, j) = *std::advance(begin, j - gap);
      }
      *std::advance(begin, j) = temp;
    }
  }
}


int main()
{
  
}
