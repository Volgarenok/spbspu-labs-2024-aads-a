#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <cassert>
#include "node.hpp"

namespace stepanov
{
  template < typename T>
  class List;

  template < typename T>
  class ConstIterator;

  template < typename T>
  class Iterator: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
    public:
      using this_type = Iterator< T >;
      Iterator():
        node_(nullptr)
      {}
      Iterator(Node< T > * node):
        node_(node)
      {}
      ~Iterator() = default;
      Iterator(const this_type &) = default;
      this_type & operator=(const this_type &) = default;
      this_type & operator++()
      {
        assert(node_ != nullptr);
        node_ = node_->next_;
        return *this;
      }
      this_type operator++(int)
      {
        assert(node_ != nullptr);
        this_type result(*this);
        ++(*this);
        return result;
      }
      T & operator*()
      {
        assert(node_ != nullptr);
        return node_->data_;
      }
      T * operator->()
      {
        assert(node_ != nullptr);
        return std::addressof(node_->data_);
      }
      bool operator==(const this_type & rhs) const
      {
        return node_ == rhs.node_;
      }
      bool operator!=(const this_type & rhs) const
      {
        return !(rhs == *this);
      }

    private:
      Node< T > * node_;
  };
}


#endif
