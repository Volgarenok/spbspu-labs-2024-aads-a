#include "createcontainer.hpp"
#include <random>

float piyavkin::detail::get_value(float)
{
  static std::default_random_engine generator;
  static std::uniform_real_distribution< float > dis;
  return dis(generator);
}

int piyavkin::detail::get_value(int)
{
  return std::rand();
}
