#ifndef TWOTHREETREE_HPP
#define TWOTHREETREE_HPP

#include <functional>

#include "node.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace zhalilov
{
  template < class Key, class T, class Compare = std::less < Key > >
  class TwoThree
  {
  public:
    using MapPair = std::pair < Key, T >;
    using iterator = TwoThreeIterator < MapPair >;
    using const_iterator = TwoThreeIterator < MapPair >;

    TwoThree();

    T &at(const Key &);
    const T &at(const Key &) const;
    T &operator[](const Key &);
    T &operator[](Key &&);

    bool empty();
    size_t size();

    void clear();
    void swap();

    iterator find(const Key &);
    const_iterator find(const Key &) const;

  private:
    detail::Node < MapPair > *head_;
    size_t size_;
  };
}

#endif
