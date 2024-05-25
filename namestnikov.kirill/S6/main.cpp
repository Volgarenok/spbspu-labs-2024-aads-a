#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include "shell_sort.hpp"
#include "selection_sort.hpp"

template< class T >
T generateNumber(T minNumber, T maxNumber)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution< float > dist(minNumber, maxNumber);
  return static_cast< T >(dist(gen));
}

template< class T >
std::vector< T > generateNumbers(size_t size)
{
  std::vector< T > data(size);
  for (size_t i = 0; i < size; ++i)
  {
    data[i] = generateNumber< T >(-1000, 1000);
  }
  return data;
}

int main()
{
  using namespace namestnikov;
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
  std::vector< int > vec = generateNumbers< int >(20);
  for (auto it = vec.begin(); it != vec.end(); ++it)
  {
    std::cout << *it << "|||";
  }
  doSelectionSort(vec.begin(), vec.size(), std::less< int >());
  for (auto it = vec.begin(); it != vec.end(); ++it)
  {
    std::cout << *it << "|||";
  }
}
