#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

namespace ishmuratov
{
  template<class T>
  struct less
  {
    constexpr bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs < rhs;
    }
  };
}

#endif
