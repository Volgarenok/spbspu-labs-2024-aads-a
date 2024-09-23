#ifndef KEY_SUMM_HPP
#define KEY_SUMM_HPP

#include <utility>
#include <string>

namespace sivkov
{
  struct KeySum
  {
  public:
    KeySum();
    void operator()(const std::pair< const int, std::string >& key_value);
    std::string string_;
    int key_;
  };
}

#endif

