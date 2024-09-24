#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <cassert>
#include <iterator>
#include <forward_list>
#include "node.hpp"
#include "list.hpp"

namespace vojuck
{
  template < typename T >
  class List;
  template < typename T >
  struct ConstIteratorList: public std::iterator< std::forward_iterator_tag, T >
  {
    public:
      using this_t = ConstIteratorList< T >;
      ConstIteratorList():
        node_(nullptr)
      {}
      ConstIteratorList(details::Node< T > * node):
        node_(node)
      {}
      ~ConstIteratorList() = default;

      ConstIteratorList(const this_t &) = default;
      ConstIteratorList(const IteratorList< T > & other):
        node_(other.node_)
      {}
      this_t & operator=(const this_t &) = default;
      this_t & operator++()
      {
        assert(node_ != nullptr);
        node_ = node_->next_;
        return *this;
      }
      this_t operator++(int)
      {
        assert(node_ != nullptr);
        this_t result(*this);
        ++(*this);
        return result;
      }
      const T & operator*() const
      {
        //assert(node_ != nullptr);
        //return std::addressof(node_->data_);
        return node_->data_;
      }
      const T * operator->() const
      {
        //assert(node_ != nullptr);
        return std::addressof(node_->data_);
        //return node_->data_;
      }

      bool operator==(const this_t & rhs) const
      {
        return node_ == rhs.node_;
      }
      bool operator!=(const this_t & rhs) const
      {
        return !(rhs == *this);
      }
    private:
      details::Node< T > * node_;

  };

}


#endif
