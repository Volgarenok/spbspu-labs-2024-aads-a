#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <iterator>
#include "Node.hpp"

namespace vyzhanov
{
  template< typename T >
  class List;

  template< typename T >
  class ConstBiIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class  List< T >;
    using citerator = ConstBiIterator< T >;

  public:
    ConstBiIterator();
    ConstBiIterator(const citerator&) = default;
    ~ConstBiIterator() = default;

    citerator& operator=(const citerator&) = default;

    bool operator==(const citerator&) const;
    bool operator!=(const citerator&) const;

    citerator& operator++();
    citerator& operator--();
    citerator operator++(int);
    citerator operator--(int);

    const T& operator*() const;
    const T* operator->() const;

  private:
    Node< T >* node_;
    explicit ConstBiIterator(Node< T >* node);
  };

  template< typename T >
  ConstBiIterator< T >::ConstBiIterator() :
    node_(nullptr)
  {}

  template< typename T >
  ConstBiIterator< T >::ConstBiIterator(Node< T >* node) :
    node_(node)
  {}

  template < typename T >
  bool ConstBiIterator< T >::operator==(const citerator& obj) const
  {
    return node_ == obj.node_;
  }

  template< typename T >
  bool ConstBiIterator< T >::operator!=(const citerator& obj) const
  {
    return !(node_ == obj.node_);
  }

  template< typename T >
  ConstBiIterator< T >& ConstBiIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ConstBiIterator< T >& ConstBiIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  ConstBiIterator< T >  ConstBiIterator< T >::operator++(int)
  {
    citerator temp = *this;
    node_ = node_->next_;
    return temp;
  }

  template< typename T >
  ConstBiIterator< T >  ConstBiIterator< T >::operator--(int)
  {
    citerator temp = *this;
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  const T& ConstBiIterator< T >::operator*() const
  {
    return node_->data_;
  }

  template< typename T >
  const T* ConstBiIterator< T >::operator->() const
  {
    return std::addressof(node_->data_);
  }
}

#endif
