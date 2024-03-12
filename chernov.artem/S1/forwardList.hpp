#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include "node.hpp"
#include <cstddef>
#include <iostream>

template < typename T >
class List
{
public:

  bool isEmpty() const
  {
    return size_ == 0;
  }

  size_t getSize() const
  {
    return size_;
  }

private:

  Node< T >* head_;
  Node< T >* tail_;
  size_t size_;
};

#endif
