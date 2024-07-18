#include "summator.hpp"
#include <operators.hpp>

void zaitsev::summator::operator()(const std::pair< const long long, std::string >& key_value)
{
  key_sum = safePlus(key_sum, key_value.first);
  val_sum += (val_sum.empty() ? key_value.second : " " + key_value.second);
}
