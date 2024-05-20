#include "randomGenerators.hpp"

#include <random>

void zhalilov::fillRandomInts(std::deque< int > &nums, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    nums[i] = std::rand();
  }
}

void zhalilov::fillRandomFloats(std::deque< float > &nums, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    auto upper = static_cast< float >(std::rand());
    auto lower = static_cast< float >(std::rand());
    nums[i] = lower == 0.0 ? upper : upper / lower;
  }
}
