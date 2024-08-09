#ifndef SUMMATOR_HPP
#define SUMMATOR_HPP
#include <string>

namespace zaitsev
{
  struct summator
  {
    void operator()(const std::pair< const long long, std::string >& key_value);
    long long key_sum = 0;
    std::string val_sum = "";
  };
}
#endif
