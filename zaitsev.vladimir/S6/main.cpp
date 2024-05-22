#include <random>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <forward_list.hpp>
#include <vector>
#include <deque>

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

template< class ForwardIt, class Comapare >
void bucketSort(ForwardIt begin, ForwardIt end, Comapare cmp, size_t size = 0)
{

}

int main(int argc, char** argv)
{
  constexpr size_t size = 10;
  using namespace zaitsev;
  float v[size];
  float_generator gen(0, 1000);
  std::generate_n(v, size, gen);
  ForwardList< float > lst1(v, v + size);
  ForwardList< float > lst2(v, v + size);
  std::deque< float > lst3(v, v + size);
  std::copy(lst1.begin(), lst1.end(), std::ostream_iterator< float >(std::cout, " "));
  std::cout << '\n';
  shellSort(lst1.begin(), lst1.end(), std::less< float >{});
  shellSort(lst3.begin(), lst3.end(), std::less< float >{});
  lst2.sort(std::less< float >{});
  std::copy(lst1.begin(), lst1.end(), std::ostream_iterator< float >(std::cout, " "));
  std::cout << '\n';
  std::copy(lst2.begin(), lst2.end(), std::ostream_iterator< float >(std::cout, " "));
  std::cout << '\n';
  std::copy(lst3.begin(), lst3.end(), std::ostream_iterator< float >(std::cout, " "));
  return 0;
}
