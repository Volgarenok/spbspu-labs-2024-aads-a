#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

namespace zakozhurnikova
{
  template< typename T >
  struct Comparator
  {
    bool operator()(T a, T b) const
    {
      return a < b;
    }
  };
}

#endif
