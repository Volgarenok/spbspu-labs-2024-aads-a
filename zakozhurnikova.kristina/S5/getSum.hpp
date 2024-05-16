#ifndef GETSUM_HPP
#define GETSUM_HPP
#include <limits>
#include <stdexcept>

namespace zakozhurnikova
{
  struct KeySum
  {
    KeySum();
    void operator()(int data);
    int getResult() const;

  private:
    int result_;
  };
}

#endif
