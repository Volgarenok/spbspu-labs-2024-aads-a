#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>
#include <bidirectional_node.hpp>
#include <const_bidirectional_iterator.hpp>

namespace namestnikov
{
  template< class T >
  class List;

  template< class T >
  class ConstListIterator;

  template< class T >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
    friend class ConstListIterator< T >;
  public:
    using node_t = detail::BaseListNode;
    using iterator = ListIterator< T >;
    using const_iterator = ConstListIterator< T >;
    ListIterator():
      node_(nullptr)
    {}
    ListIterator(const iterator &) = default;
    iterator & operator=(const iterator &) = default;
    ListIterator(iterator &&) = default;
    bool operator==(const iterator & other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const iterator & other) const
    {
      return !(*this == other);
    }
    bool operator==(const_iterator & other) const
    {
      return (*this == other);
    }
    bool operator!=(const_iterator & other) const
    {
      return (*this != other);
    }
    T & operator*()
    {
      return (dynamic_cast< detail::ListNode< T > * >(node_))->data;
    }
    const T & operator*() const
    {
      return (dynamic_cast< detail::ListNode< T >* >(node_))->data;
    }
    T * operator->()
    {
      return std::addressof(**this);
    }
    const T * operator->() const
    {
      return std::addressof(**this);
    }
    iterator & operator++()
    {
      node_ = node_->next;
      return *this;
    }
    iterator operator++(int)
    {
      iterator temp(*this);
      ++(*this);
      return temp;
    }
    iterator & operator--()
    {
      node_ = node_->prev;
      return *this;
    }
    iterator operator--(int)
    {
      iterator temp(*this);
      --(*this);
      return temp;
    }
  private:
    node_t * node_;
    explicit ListIterator(node_t * ptr):
      node_(ptr)
    {}
  };
}

#endif
