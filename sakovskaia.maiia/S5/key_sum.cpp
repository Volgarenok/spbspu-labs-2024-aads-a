#include "key_sum.hpp"
#include <utility>
#include <string>
#include <limits>
#include <stdexcept>
#include <queue>

namespace sakovskaia
{
  KeySum::KeySum():
    str_(),
    key_(0)
  {}

  void KeySum::operator()(const std::pair<const int, std::string> & value)
  {
    if (value.first > 0 && key_ > std::numeric_limits< int >::max() - value.first)
    {
      throw std::out_of_range("<OVERFLOW>");
    }
    else if (value.first < 0 && key_ < std::numeric_limits< int >::min() - value.first)
    {
      throw std::out_of_range("<UNDERFLOW>");
    }
    key_ += value.first;

    if (value.second != "")
    {
      str_ += " " + value.second;
    }
  }
}
