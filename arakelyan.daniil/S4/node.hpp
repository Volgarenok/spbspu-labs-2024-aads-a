#ifndef NODE_HPP
#define NODE_HPP

namespace arakelyan
{
  namespace detail
  {
    enum color_t
    {
      RED = 0,
      BLACK = 1
    };

    template < class T >
    struct Node
    {
      T data_;
      color_t color_ = color_t::BLACK;
      Node *right_;
      Node *left_;
      Node *parent_;

      Node() = delete;
      explicit Node(const T &val);
    };

    template < class T >
    Node< T >::Node(const T &val):
      data_(val),
      color_(color_t::RED),
      right_(nullptr),
      left_(nullptr),
      parent_(nullptr)
    {}
  }
}
#endif
