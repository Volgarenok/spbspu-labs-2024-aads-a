#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iterator>
#include <node.hpp>
#include <const_iterators.hpp>

namespace namestnikov
{
  template < class T >
  class ForwardList;

  template < class T >
  class ConstForwardIterator;

  template < class T >
  class ForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class ForwardList< T >;
    friend class ConstForwardIterator< T >;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using node_t = detail::Node< T >;
  public:
    ForwardIterator():
      node_(nullptr)
    {}
    ForwardIterator(const iterator &) = default;
    iterator & operator=(const iterator &) = default;
    ForwardIterator(ForwardIterator && other) noexcept = default;
    iterator & operator++()
    {
      node_ = node_->next_;
      return *this;
    }
    iterator operator++(int)
    {
      iterator temp(*this);
      ++(*this);
      return temp;
    }
    bool operator!=(const iterator & other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const iterator & other) const
    {
      return (node_ == other.node_);
    }
    bool operator!=(const_iterator & other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const_iterator & other) const
    {
      return (node_ == other.node_);
    }
    T & operator*()
    {
      return node_->data_;
    }
    const T & operator*() const
    {
      return node_->data_;
    }
    T * operator->()
    {
      return std::addressof(node_->data_);
    }
    const T * operator->() const
    {
      return std::addressof(node_->data_);
    }
    ~ForwardIterator() = default;
  private:
    node_t * node_;
    explicit ForwardIterator(node_t * node):
      node_(node)
    {}
  };
}
#endif
