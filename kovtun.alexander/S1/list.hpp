#ifndef LIST_HPP
#define LIST_HPP

#include "const_iterator.hpp"

namespace kovtun
{
  template< typename T >
  class List
  {
  public:
    List() :
        head_(nullptr),
        tail_(nullptr),
        size_(0)
    {};
    ~List() = default;

  private:
    Node< T > * head_;
    Node< T > * tail_;
    size_t size_;
  };
}

#endif
