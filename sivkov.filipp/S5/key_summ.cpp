#include "key_summ.hpp"
#include <utility>
#include <string>
#include <limits>
#include <stdexcept>
#include <queue.hpp>

namespace sivkov
{
  KeySum::KeySum():
    string_(),
    key_(0)
  {}

  void KeySum::operator()(const std::pair<const int, std::string>& key_value)
  {
    if (key_value.first > 0 && key_ > std::numeric_limits< int >::max() - key_value.first)
    {
      throw std::out_of_range("overflow");
    }
    else if (key_value.first < 0 && key_ < std::numeric_limits< int >::min() - key_value.first)
    {
      throw std::out_of_range("underflow");
    }
    key_ += key_value.first;

    if (key_value.second != "")
    {
      string_ += " " + key_value.second;
    }
  }
}

