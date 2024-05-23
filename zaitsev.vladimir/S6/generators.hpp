#ifndef GENERATORS_HPP
#define GENERATORS_HPP
#include <random>

template< typename T >
class generator;

template<>
class generator< int >
{
public:
  generator(int a, int b):
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

template<>
class generator<float>
{
public:
  generator(float a, float b):
    gen(std::random_device()()),
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


#endif
