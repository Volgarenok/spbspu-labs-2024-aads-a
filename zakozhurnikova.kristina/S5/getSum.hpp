#ifndef GETSUM_HPP
#define GETSUM_HPP
#include <limits>
#include <stdexcept>

namespace zakozhurnikova
{
  struct KeySum
  {
    int maxNum = std::numeric_limits< int >::max();
    void operator()(const int& data)
    {
      if (maxNum - result_ < data)
      {
        throw std::out_of_range("Error: Addition overflow");
      }
      result_ += data;
    }

    int result_ = 0;
  };
}

#endif
