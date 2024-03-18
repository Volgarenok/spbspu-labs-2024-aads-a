#ifndef BILIST_HPP
#define BILIST_HPP

namespace chistyakov
{
  template< typename T >
  struct BiList
  {
    BiList(T value):
      value_(value),
      next_(nullptr),
      previous_(nullptr)
    {}

    ~BiList() = default;

    T value_;
    BiList * next_;
    BiList * previous_;
  };
}

#endif
