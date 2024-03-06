#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"

namespace baranov
{
  template< class T >
  class List
  {
    public:
      List():
        head_(nullptr),
        tail_(nullptr)
      {}

    private:
      Node< T > * head_;
      Node< T > * tail_;
  };
}

#endif

