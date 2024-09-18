#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace chistyakov
{
  template< typename T >
  class List;

  template< typename T >
  class Iterator : public std::iterator < std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
    public:
      Iterator():
        node_(nullptr)
      {}
      Iterator(const Iterator & value):
        node_(value.node_)
      {}

      ~Iterator() noexcept = default;

      Iterator< T > & operator=(const Iterator< T > & ) noexcept = default;

      Iterator< T > & operator++()
      {
        node_ = node_->next;
        return *this;
      }

      Iterator< T > & operator++(int)
      {
        Iterator< T > now(*this);
        ++(*this);
        return now;
      }

      Iterator< T > & operator--()
      {
        node_ = node_->previous;
        return *this;
      }

      Iterator< T > & operator--(int)
      {
        Iterator now(*this);
        --(*this);
        return now;
      }

      bool operator==(const Iterator< T > & rhs) const noexcept
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const Iterator< T > & rhs) const noexcept
      {
        return !(rhs == *this);
      }

      T & operator*()
      {
        return node_->value;
      }

      T * operator->()
      {
        return std::addressof(node_->value);
      }

      const T & operator*() const
      {
        return node_->value;
      }

      const T * operator->() const
      {
        return std::addressof(node_->value);
      }

    private:
      detail::Node< T > * node_;

      explicit Iterator(detail::Node< T > * value) noexcept:
        node_(value)
      {}
  };
}

#endif
