#ifndef CONST_ITERATORS_HPP
#define CONST_ITERATORS_HPP

#include <iterator>
#include <iterators.hpp>

namespace namestnikov
{
  template <  class T >
  class ForwardList;

  template < class T >
  class ForwardIterator;

  template < class T >
  class ConstForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class ForwardIterator< T >;
    friend class ForwardList< T >;
    using const_iterator = ConstForwardIterator< T >;
    using iterator = ForwardIterator< T >;
    using node_t = detail::Node< T >;
  public:
    ConstForwardIterator():
      node_(nullptr)
    {}
    ConstForwardIterator(const const_iterator &) = default;
    const_iterator & operator=(const const_iterator &) = default;
    ConstForwardIterator(ConstForwardIterator && other) noexcept = default;
    const_iterator & operator++()
    {
      node_ = node_->next_;
      return *this;
    }
    const_iterator operator++(int)
    {
      const_iterator temp(*this);
      ++(*this);
      return temp;
    }
    bool operator!=(const const_iterator & other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const const_iterator & other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(iterator & other) const
    {
      return node_ != other.node_;
    }
    bool operator==(iterator & other) const
    {
      return node_ == other.node_;
    }
    const T & operator*() const
    {
      return node_->data_;
    }
    const T * operator->() const
    {
      return std::addressof(node_->data_);
    }
    ~ConstForwardIterator() = default;
  private:
    node_t * node_;
    explicit ConstForwardIterator(node_t * node):
      node_(node)
    {}
  };
}

#endif
