#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "biList.hpp"

namespace chistyakov
{
  template< typename T >
  class Iterator
  {
    public:
      Iterator():
        node_(nullptr)
      {}

      Iterator(const Iterator & val):
        node_(val.node_)
      {}

      Iterator(BiList< T > * val):
        node_(val)
      {}

      ~Iterator() = default;
      Iterator< T > & operator=(const Iterator< T > & ) = default;

      Iterator< T > & operator++()
      {
        if (node_ != nullptr)
        {
          node_ = node_->next_;
        }

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
        if (node_ != nullptr)
        {
          node_ = node_->previous_;
        }

        return *this;
      }

      Iterator< T > & operator--(int)
      {
        Iterator now(*this);
        --(*this);
        return now;
      }

      Iterator< T > & operator+(int num)
      {
         Iterator now(*this);

         for (int i = 0; i < num; ++i)
         {
           ++now;
         }

         return now;
      }

      Iterator< T > & operator-(int num)
      {
        Iterator< T > now(*this);

        for (int i = 0; i < num; ++i)
        {
          --now;
        }

        return now;
      }

      bool operator==(const Iterator< T > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const Iterator< T > & rhs) const
      {
        return !(rhs == *this);
      }

      T & operator*()
      {
        return node_->value_;
      }

      T * operator->()
      {
        return std::addressof(node_->value_);
      }

      BiList< T > * get_BiList()
      {
        return node_;
      }

    private:
      BiList< T > * node_;
  };
}

#endif
