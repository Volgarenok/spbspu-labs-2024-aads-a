#include <algorithm>
#include <iostream>
#include <list>

template< class Iter, class Compare >
void doShellSort(Iter begin, size_t size, Compare compare)
{
  for (size_t gap = size / 2; gap > 0; gap /= 2)
  {
    for (size_t i = gap; i < size; ++i)
    {
      auto temp = *std::next(begin, i);
      size_t j = i;
      for (; ((j >= gap) && (compare(temp, *std::next(begin, j - gap)))); j -= gap)
      {
        *std::next(begin, j) = *std::next(begin, j - gap);
      }
      *std::next(begin, j) = temp;
    }
  }
}

template< class Iter, class Compare >
void doSelectionSort(Iter begin, size_t size, Compare compare)
{
  for (size_t i = 0; i < size - 1; ++i)
  {
    size_t minIndex = i;
    for (size_t j = i + 1; j < size; ++j)
    {
      if (compare(*std::next(begin, j), *std::next(begin, minIndex)))
      {
        minIndex = j;
      }
    }
    if (minIndex != i)
    {
      std::swap(*std::next(begin, minIndex), *std::next(begin, i));
    }
  }
}

int main()
{
  std::list< int > temp({4, 1, 3, 2});
  doShellSort(temp.begin(), temp.size(), std::less< int >());
  for (auto it = temp.begin(); it != temp.end(); ++it)
  {
    std::cout << *it;
  }
  doSelectionSort(temp.begin(), temp.size(), std::less< int >());
  for (auto it = temp.begin(); it != temp.end(); ++it)
  {
    std::cout << *it;
  }
}
