#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace baranov
{
  template< typename Key, typename T >
  struct Node
  {
    std::pair< Key, T > data_;
    Node< Key, T > * left_;
    Node< Key, T > * right_;
    Node< Key, T  > * parent_;
  };
}

#endif

