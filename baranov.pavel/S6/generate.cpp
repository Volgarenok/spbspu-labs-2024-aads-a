#include "generate.hpp"

float baranov::getRandomNumber(std::default_random_engine & generate, const float)
{
  std::uniform_real_distribution< float > dis(-1000, 1000);
  return dis(generate);
}

