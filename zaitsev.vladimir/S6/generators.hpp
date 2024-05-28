#ifndef GENERATORS_HPP
#define GENERATORS_HPP
#include <random>

namespace zaitsev
{
  template< typename T >
  class generator;

  template<>
  class generator< int >
  {
  public:
    generator(int a, int b, int seed):
      gen(seed),
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
  class generator< float >
  {
  public:
    generator(float a, float b, int seed):
      gen(seed),
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
}
#endif
