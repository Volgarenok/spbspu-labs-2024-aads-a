#include "generate.hpp"
#include <random>

int zakozhurnikova::detail::randomNumberInt()
{
  static std::default_random_engine generator;
  static std::uniform_int_distribution< int > dis(-1000, 1000);
  return dis(generator);
}

float zakozhurnikova::detail::randomNumberFloat()
{
  static std::default_random_engine generate;
  static std::uniform_real_distribution< float > dis(-1000, 1000);
  return dis(generate);
}
