#ifndef ITERATOR_HPP
#define ITERATIR_HPP

#include "list.hpp"

namespace nikitov
{
  template< typename T >
  class Iterator: public std::iterator< std::input_iterator_tag, T >
  {
    friend class List;
  public:
    T& Iterator::reference operator*() const;
    T* Iterator operator->() const;
    Iterator& operator++();
    Iterator operator++( int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
  private:
    List< T >* node;
  };
}
#endif
