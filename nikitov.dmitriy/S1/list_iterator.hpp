#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <iterator>

namespace nikitov
{
  template< typename T >
  class Node;

  template< typename T >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    ListIterator(Node< T >* node);
    ListIterator(const ListIterator&) = default;
    ~ListIterator() = default;

    T& operator*();
    T* operator->();
    const T& operator*() const;
    const T* operator->() const;
    ListIterator< T >& operator=(const ListIterator&) = default;
    ListIterator< T >& operator++();
    ListIterator< T > operator++(int);
    ListIterator< T >& operator--();
    ListIterator< T > operator--(int);
    bool operator==(const ListIterator& other) const;
    bool operator!=(const ListIterator& other) const;

    ListIterator< T >& advance(int n);

  private:
    Node< T >* node_;
  };

  template< typename T >
  ListIterator< T >::ListIterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  T& ListIterator< T >::operator*()
  {
    return node_->value_;
  }

  template< typename T >
  T* ListIterator< T >::operator->()
  {
    return std::addressof(node_->value_);
  }

  template< typename T >
  const T& ListIterator< T >::operator*() const
  {
    return node_.value;
  }

  template< typename T >
  const T* ListIterator< T >::operator->() const
  {
    return std::addressof(node_.value);
  }

  template< typename T >
  ListIterator< T >& ListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ListIterator< T > ListIterator< T >::operator++(int)
  {
    ListIterator temp(*this);
    node_ = node_->next_;
    return temp;
  }

  template< typename T >
  ListIterator< T >& ListIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  ListIterator< T > ListIterator< T >::operator--(int)
  {
    ListIterator temp(*this);
    node_ = node_->prev_;
    return temp;
  }

  template< typename T >
  bool ListIterator< T >::operator==(const ListIterator& other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool ListIterator< T >::operator!=(const ListIterator& other) const
  {
    return node_ != other.node_;
  }

  template< typename T >
  ListIterator< T >& ListIterator< T >::advance(int n)
  {
    if (n > 0)
    {
      for (int i = 0; i != n; ++i)
      {
        node_ = node_->next_;
      }
    }
    else if (n < 0)
    {
      for (int i = 0; i != -n; ++i)
      {
        node_ = node_->prev_;
      }
    }
    return *this;
  }
}
#endif
