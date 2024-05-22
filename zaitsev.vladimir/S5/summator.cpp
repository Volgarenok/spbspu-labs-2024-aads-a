#include "summator.hpp"
#include <operators.hpp>

void zaitsev::summator::operator()(const std::pair< const long long, std::string >& key_value) {
  key_sum_ = safePlus(key_sum_, key_value.first);
  val_sum_ += (val_sum_.empty() ? key_value.second : " " + key_value.second);
}
