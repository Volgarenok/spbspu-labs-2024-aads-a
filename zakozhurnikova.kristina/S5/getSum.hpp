#ifndef GETSUM_HPP
#define GETSUM_HPP
#include <limits>
#include <stdexcept>

namespace zakozhurnikova
{
  struct KeySum
  {
    void operator()(int data);

    int result_ = 0;
  };
}

#endif
