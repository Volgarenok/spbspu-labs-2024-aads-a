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
    public:
      Node();
      explicit Node(const T& value);
      Node(T&& value);
      void swap(Node< T >& other) noexcept;
      ~Node() = default;
      T value_;
      Node* prev_;
      Node* next_;
    };

    template< class T >
    Node< T >::Node():
      Node(T())
    {};

    template< class T >
    Node< T >::Node(const T& value):
      value_(value),
      prev_(nullptr),
      next_(nullptr)
    {}

    template< class T >
    Node< T >::Node(T&& value):
      value_(std::move(value)),
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
