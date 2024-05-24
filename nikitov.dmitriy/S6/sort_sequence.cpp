#include "sort_sequence.hpp"

int nikitov::detail::generateValue(int)
{
  return std::rand();
}

float nikitov::detail::generateValue(float)
{
  return static_cast <float> (std::rand());
}