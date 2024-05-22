#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <forward_list.hpp>
#include <vector>

class int_generator
{
public:
  int_generator(int a, int b):
    gen(std::random_device()()),
    distr(a, b)
  {}
  int operator()()
  {
    return distr(gen);
  }
private:
  std::mt19937 gen;
  std::uniform_int_distribution< int > distr;
};

class float_generator
{
public:
  float_generator(float a, float b):
    gen(),
    distr(a, b)
  {}
  float operator()()
  {
    return distr(gen);
  }
private:
  std::mt19937 gen;
  std::uniform_real_distribution< float > distr;
};

template< class ForwardIt, class Comapare >
void shellSort(ForwardIt begin, ForwardIt end, Comapare cmp, size_t size = 0)
{
  if (size == 0)
  {
    ForwardIt copy = begin;
    while (copy != end)
    {
      ++size;
      ++copy;
    }
  }
  size_t diff = size;
  while (diff > 1)
  {
    diff /= 2;
    ForwardIt front_start = begin;
    std::advance(front_start, diff);
    size_t swaps = 1;
    while (swaps != 0)
    {
      ForwardIt front = front_start;
      ForwardIt back = begin;
      swaps = 0;
      while (front != end)
      {
        if (cmp(*front, *back))
        {
          std::swap(*back, *front);
          ++swaps;
        }
        ++front;
        ++back;
      }
    }
  }
}


int main()
{
  constexpr size_t size = 300;
  using namespace zaitsev;
  int v[size];
  int_generator gen(0, 1000);
  std::generate_n(v, size, gen);
  ForwardList< int > lst(v, v + size);
  std::copy(lst.begin(), lst.end(), std::ostream_iterator< int >(std::cout, " "));
  std::cout << '\n';
  shellSort(lst.begin(), lst.end(), std::less< int >{});
  std::copy(lst.begin(), lst.end(), std::ostream_iterator< int >(std::cout, " "));
  return 0;
}
