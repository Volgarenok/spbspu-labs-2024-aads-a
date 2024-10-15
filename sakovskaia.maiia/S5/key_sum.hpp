#ifndef KEY_SUM_HPP
#define KEY_SUM_HPP
#include <utility>
#include <string>
#include <limits>
#include <stdexcept>
#include <queue>

namespace sakovskaia
{
  struct KeySum
  {
  public:
    KeySum();
    void operator()(const std::pair< const int, std::string > & value);
    std::string str_;
    int key_;
  };
}

#endif
