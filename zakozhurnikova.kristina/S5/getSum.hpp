#ifndef GETSUM_HPP
#define GETSUM_HPP
#include <limits>
#include <stdexcept>

namespace zakozhurnikova
{
  struct KeySum
  {
    int maxNum = std::numeric_limits< int >::max();
    int minNum = std::numeric_limits< int >::min();
    void operator()(int data)
    {
      if (result_ >= 0  && (maxNum - result_ < data))
      {
        throw std::out_of_range("Error: Addition overflow");
      }
      else if (result_ < 0 && (result_ <= minNum - data))
      {
        throw std::out_of_range("Error: Addition underflow");
      }
      result_ += data;
    }

    int result_ = 0;
  };
}

#endif
