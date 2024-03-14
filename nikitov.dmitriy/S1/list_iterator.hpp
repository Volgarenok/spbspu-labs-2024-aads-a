#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <iterator>

namespace nikitov
{
  template< class T >
  class List;

  template< class T >
  class Node;

  template< class T >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
  public:
    ListIterator();
    ListIterator(Node< T >* node);
    ListIterator(const ListIterator< T >&) = default;
    ~ListIterator() = default;

    ListIterator< T >& operator=(const ListIterator< T >&) = default;

    ListIterator< T >& operator++();
    ListIterator< T > operator++(int);
    ListIterator< T >& operator--();
    ListIterator< T > operator--(int);

    T& operator*();
    T* operator->();

    bool operator==(const ListIterator< T >& other) const;
    bool operator!=(const ListIterator< T >& other) const;

    ListIterator< T >& advance(int n);

  private:
    Node< T >* node_;
  };

  template< class T >
  ListIterator< T >::ListIterator():
    node_(nullptr)
  {}

  template< class T >
  ListIterator< T >::ListIterator(Node< T >* node):
    node_(node)
  {}

  template< class T >
  ListIterator< T >& ListIterator< T >::operator++()
  {
    node_ = node_->next_;
    return *this;
  }

  template< class T >
  ListIterator< T > ListIterator< T >::operator++(int)
  {
    ListIterator< T > temp(*this);
    node_ = node_->next_;
    return temp;
  }

  template< class T >
  ListIterator< T >& ListIterator< T >::operator--()
  {
    node_ = node_->prev_;
    return *this;
  }

  template< class T >
  ListIterator< T > ListIterator< T >::operator--(int)
  {
    ListIterator< T > temp(*this);
    node_ = node_->prev_;
    return temp;
  }

  template< class T >
  T& ListIterator< T >::operator*()
  {
    if (node_->next_ == nullptr)
    {
      throw std::logic_error("Error: Dereferencing of std::end()");
    }
    return node_->value_;
  }

  template< class T >
  T* ListIterator< T >::operator->()
  {
    if (node_->next_ == nullptr)
    {
      throw std::logic_error("Error: Dereferencing of std::end()");
    }
    return std::addressof(node_->value_);
  }

  template< class T >
  bool ListIterator< T >::operator==(const ListIterator< T >& other) const
  {
    return node_ == other.node_;
  }

  template< class T >
  bool ListIterator< T >::operator!=(const ListIterator< T >& other) const
  {
    return node_ != other.node_;
  }

  template< class T >
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
