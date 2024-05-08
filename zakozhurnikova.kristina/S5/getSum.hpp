#ifndef GETSUM_HPP
#define GETSUM_HPP
#include <limits>
#include <stdexcept>

namespace zakozhurnikova
{
  struct KeySum
  {
    long long maxNum = std::numeric_limits< long long >::max();
    long long minNum = std::numeric_limits< long long >::min();
    void operator()(long long data)
    {
      if (data < 0 && result_ < minNum - data)
      {
        throw std::out_of_range("Error: Addition overflow");
      }
      else if (data > 0 && result_ > maxNum - data)
      {
        throw std::out_of_range("Error: Addition underflow");
      }
      result_ += data;
    }

    long long result_ = 0;
  };
}

#endif
