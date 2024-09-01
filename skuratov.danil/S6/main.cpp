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

template< typename T >
void printContainer(const std::deque< T >& container)
{
  for (const auto& item : container)
  {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

template< typename T >
void printContainer(const List< T >& container)
{
  for (auto it = container.cbegin(); it != container.cend(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}

template< typename T >
void printContainer(const std::forward_list< T >& container)
{
  for (const auto& item : container)
  {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

int main(int argc, char* argv[])
{
  using namespace skuratov;
  if (argc != 4)
  {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }

  std::string sortType = argv[1];
  std::string order = argv[2];
  std::string type = argv[3];
  size_t size = std::stoi(argv[4]);
  bool ascending = order == "ascending";

  srand(static_cast< unsigned int >(time(0)));

  std::deque< int > deq;
  List< int > dblList;
  std::forward_list< int > fwdList;

  if (type == "ints")
  {
    generateRandomNumbers(deq, size);
    for (const auto& number : deq)
    {
      dblList.pushBack(number);
      fwdList.push_front(number);
    }
  
    if (sortType == "shell")
    {
      if (ascending)
      {
        shellSort(deq.begin(), deq.end(), std::less< int >());
        shellSort(dblList.ñbegin(), dblList.ñend(), std::less< int >());
        shellSort(fwdList.begin(), fwdList.end(), std::less< int >());
      }
      else
      {
        shellSort(deq.begin(), deq.end(), std::greater< int >());
        shellSort(dblList.ñbegin(), dblList.ñend(), std::greater< int >());
        shellSort(fwdList.begin(), fwdList.end(), std::greater< int >());
      }
    }
    else if (sortType == "shaker")
    {
      if (ascending)
      {
        shakerSort(deq.begin(), deq.end(), std::less< int >());
        shakerSort(dblList.ñbegin(), dblList.ñend(), std::less< int >());
        shakerSort(fwdList.begin(), fwdList.end(), std::less< int >());
      }
      else
      {
        shakerSort(deq.begin(), deq.end(), std::greater< int >());
        shakerSort(dblList.ñbegin(), dblList.ñend(), std::greater< int >());
        shakerSort(fwdList.begin(), fwdList.end(), std::greater< int >());
      }
    }
    else
    {
      std::cerr << "Invalid sort type" << '\n';
      return 1;
    }

    std::cout << "Sorted using std::deque: ";
    printContainer(deq);
    std::cout << "Sorted using custom List: ";
    printContainer(dblList);
    std::cout << "Sorted using std::forward_list: ";
    printContainer(fwdList);
  }
  else
  {
    std::cerr << "Invalid type" << '\n';
    return 1;
  }
  return 0;
}
