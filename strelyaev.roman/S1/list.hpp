#ifndef LIST_HPP
#define LIST_HPP

namespace strelyaev
{
  template< typename T >
  struct Node
  {
    Node(T value):
      value_(value),
      next_(nullptr),
      prev_(nullptr)
    {}
    ~Node() = default;
    T value_;
    Node* next_;
    Node* prev_;
  };

  template< typename T >
  class List
  {
    public:
    List(Node< T >* head, Node< T >* tail):
      head_(head),
      tail_(tail)
    {}
    private:
     Node< T >* head_;
     Node< T >* tail_;
  };
}
#endif
