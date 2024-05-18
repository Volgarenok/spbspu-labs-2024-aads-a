#include "createcontainer.hpp"

float piyavkin::detail::get_value(float)
{
  std::default_random_engine generator;
  std::uniform_real_distribution<> dis(-1.0, 1.0);
  return dis(generator);
}

int piyavkin::detail::get_value(int)
{
  return std::rand();
}