#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace nikitov
{
  namespace detail
  {
    template< class T >
    struct Node
    {
      T value_;
      Node* prev_;
      Node* next_;

      template< class... Args >
      Node(Args&&... args);
      ~Node() = default;

      void swap(Node< T >& other) noexcept;
    };

    template< class T >
    template< class... Args >
    Node< T >::Node(Args&&... args):
      value_(std::forward< Args >(args)...),
      prev_(nullptr),
      next_(nullptr)
    {}

    template< class T >
    void Node< T >::swap(Node< T >& other) noexcept
    {
      std::swap(value_, other.value_);
      std::swap(prev_, other.prev_);
      std::swap(next_, other.next_);
    }
  }
}
#endif
