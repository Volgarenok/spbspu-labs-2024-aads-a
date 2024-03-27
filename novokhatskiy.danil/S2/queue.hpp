#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "forward_list.hpp"

namespace novokhatskiy
{
  template < typename T > class Queue
  {

  private:
    ForwardList< T > data_;
  };
}

#endif
