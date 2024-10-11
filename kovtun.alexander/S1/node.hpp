#ifndef NODE_HPP
#define NODE_HPP

namespace kovtun
{
  template<typename T>
  struct Node
  {
    Node(Node *prev, Node *next, T val) :
        prev(prev),
        next(next),
        val(val)
    {};

    ~Node() = default;

    Node *prev;
    Node *next;
    T val;
  };
}

#endif
