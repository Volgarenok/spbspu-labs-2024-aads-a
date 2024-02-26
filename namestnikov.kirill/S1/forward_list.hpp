#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
#include "node.hpp"
#include "iterators.hpp"

namespace namestnikov
{
  template <class T>
  class ForwardList
  {
  public:
    ForwardList():
      head_(nullptr),
      size_(0),
  private:
  };
}

#endif
