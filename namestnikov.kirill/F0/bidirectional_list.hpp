#ifndef BIDIRECTIONAL_LIST_HPP
#define BIDIRECTIONAL_LIST_HPP

#include <utility>
#include "bidirectional_iterator.hpp"
#include "bidirectional_node.hpp"
#include "const_bidirectional_iterator.hpp"

namespace namestnikov
{
  template< class T >
  class List
  {
  public:
    using base_node_t = detail::BaseListNode;
    using node_t = detail::BiListNode< T >;
    using iterator = ListIterator< T >;
    using const_iterator = ConstListIterator< T >;
    List():
      size_(0),
      fakeNode_(new base_node_t())
    {}
    List(const List< T > & other):
      size_(0)
    {
      try
      {
        fakeNode_ = new base_node_t();
        auto it = other.cbegin();
        for (; it != other.cend(); ++it)
        {
          push_back(*it);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
    List< T > & operator=(const List< T > & other)
    {
      if (this != std::addressof(other))
      {
        List< T > temp(other);
        swap(temp);
      }
      return *this;
    }
    List(List< T > && other) noexcept:
      size_(other.size_),
      fakeNode_(other.fakeNode_)
    {
      other.size_ = 0;
      other.fakeNode_ = nullptr;
    }
    List< T > & operator=(List< T > && other) noexcept
    {
      if (this != std::addressof(other))
      {
        List< T > temp(std::move(other));
        swap(temp);
      }
      return *this;
    }
    ~List()
    {
      clear();
    }
  private:
    base_node_t * fakeNode_;
    size_t size_;
  };
}

#endif