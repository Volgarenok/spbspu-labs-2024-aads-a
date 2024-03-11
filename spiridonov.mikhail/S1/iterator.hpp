#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"

namespace spiridonov
{
  template <typename T>
  class iterator
  {
  private:
    Node<T>* current;

  public:
    iterator();

    ~iterator() = default;

  };

  template <typename T>
  iterator<T>::iterator()
  {}

}

#endif
