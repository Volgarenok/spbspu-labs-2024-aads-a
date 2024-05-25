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

template< class Iter >
void printData(Iter first, Iter last, std::ostream & out)
{
  auto temp = first;
  ++temp;
  for (; temp != last; ++temp)
  {
    out << *first << " ";
    ++first;
  }
  out << *first << "\n";
}

int main()
{
  using namespace namestnikov;
  std::vector< int > vec = generateNumbers< int >(20);
  printData(vec.begin(), vec.end(), std::cout);
}
