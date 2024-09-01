#include <iostream>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

#include "node.hpp"
#include "list.hpp"
#include "constIterators.hpp"

using namespace skuratov;

template< typename ForwardIterator, class Compare>
void shellSort(ForwardIterator begin, ForwardIterator end, Compare cmp)
{
  auto n = std::distance(begin, end);
  for (auto gap = n / 2; gap > 0; gap /= 2)
  {
    for (auto i = gap; i < n; ++i)
    {
      auto temp = *(begin + i);
      auto j = i;
      while (j >= gap && cmp(temp, *(begin + j - gap)))
      {
        *(begin + j) = *(begin + j - gap);
        j -= gap;
      }
      *(begin + j) = temp;
    }
  }
}

template< typename Iterator, class Compare >
void shakerSort(Iterator begin, Iterator end, Compare cmp)
{
  bool swapped = true;
  auto left = begin;
  auto right = end;
  --right;

  while (swapped)
  {
    swapped = false;

    for (auto i = left; i < right; ++i)
    {
      if (cmp(*(i + 1), *i))
      {
        std::iter_swap(i, i + 1);
        swapped = true;
      }
    }

    if (!swapped)
    {
      break;
    }
    swapped = false;
    --right;

    for (auto i = right; i > left; --i)
    {
      if (cmp(*i, *(i - 1)))
      {
        std::iter_swap(i, i - 1);
        swapped = true;
      }
    }
    ++left;
  }
}

template< typename T >
void generateRandomNumbers(std::deque< T >& container, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    container.push_back(static_cast< T >(rand() % 100));
  }
}

int main(/*int argc, char* argv[]*/)
{
  /*if (argc != 4)
  {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }*/

  srand(static_cast< unsigned int >(time(0)));

  std::deque< int > deq;
  List< int > dblList;
  std::forward_list< int > fwdList;

  for (int i = 0; i < 10; ++i)
  {
    int randomNumber = rand() % 100;
    std::cout << randomNumber << " ";
  }

  return 0;
}
