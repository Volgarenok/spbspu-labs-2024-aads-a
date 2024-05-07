#ifndef GETSUM_HPP
#define GETSUM_HPP

namespace zakozhurnikova
{
  struct KeySum
  {
    void operator()(const int data)
    {
      result_ += data;
    }

    int result_ = 0;
  };
}

#endif
