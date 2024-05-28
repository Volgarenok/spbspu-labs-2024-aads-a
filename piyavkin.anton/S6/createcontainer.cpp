#include "createcontainer.hpp"

float piyavkin::detail::get_value(std::default_random_engine& gen, float)
{
  std::uniform_real_distribution< float > dis(-1000, 1000);
  return dis(gen);
}
